#include "../include/Spiel_Laden_Speichern.hpp"

//------------------------------- Spiel laden/speichern ------------------------------------------------

SpielLaden_Speichern::SpielLaden_Speichern(Spiel* const spiel, const std::string& datei) : spiel(spiel), dateiname(datei)
{
    programm.clear();
    spieleLaden();
}

SpielLaden_Speichern::SpielLaden_Speichern(Spiel* const spiel, const std::string& datei, const std::string& programm) : spiel(spiel), dateiname(datei), programm(programm)
{
    spieleLaden();
}

SpielLaden_Speichern::~SpielLaden_Speichern()
{
    spieleSpeichern();
}

void SpielLaden_Speichern::spieleSpeichern() const
{
    std::ofstream ofs(dateiname);
    if (!ofs.is_open())
    {
        return;
    }

    for (const auto& element : spiele)
    {
        ofs << element << std::endl;
    }
}

void SpielLaden_Speichern::spieleLaden()
{
    std::ifstream ifs(dateiname);
    if (!ifs.is_open())
    {
        return;
    }

    std::string zeile;
    while(std::getline(ifs, zeile))
    {
        spiele.emplace_back(zeile);
    }
}

void SpielLaden_Speichern::spielSpeichern(bool geladenes)
{
    std::stringstream sstr;
    Datum datum;
    const std::vector<Spieler*> ptr = spiel->getSpieler();

    datum.setDatum();
    
    sstr << datum.asString() << ';';
    sstr << spiel->getAnzahlSpieler() << ';';

    for (int i = 0; i < spiel->getAnzahlSpieler(); i++)
    { 
        sstr << ptr[i]->getName() << ';';
    }

    sstr << spiel->getIndexSpieler() << ';';
    sstr << spiel->getIndexRunde() << ';';

    for (int i = 0; i < spiel->getAnzahlSpieler(); i++)
    {
        for (int j = 0; j < 20; j++)
        {
            sstr << ptr[i]->getPunkte(j) << ';';
        }
    }
    
    if (geladenes)
    {
        spiele[index] = sstr.str();
    }
    else
    {
        spiele.emplace_back(sstr.str());
    }
}

bool SpielLaden_Speichern::spielLaden()
{
    auswahl();

    if (index < 0)
    {
        return false;
    }

    int anzahl;
    int tmp;
    std::string temp;
    std::stringstream sstr(spiele[index]);

    std::getline(sstr, temp, ';');
    sstr >> anzahl;
    sstr.ignore();

    for (int i = 0; i < anzahl; i++)
    {
        std::getline(sstr, temp, ';');
        spiel->setSpieler(temp);
    }

    sstr >> tmp;
    sstr.ignore();
    spiel->setIndexSpieler(tmp);

    sstr >> tmp;
    sstr.ignore();
    spiel->setIndexRunde(tmp);

    for (int i = 0; i < anzahl; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            sstr >> tmp;
            sstr.ignore();
            if (tmp > -1)
            {
                spiel->getSpieler()[i]->punkteEintragen(tmp, j);
            }
        }
    }

    return true;
}

void SpielLaden_Speichern::auswahl()
{
    ausgabe();
    index = abfrageIntZahl("Bitte wählen (0 für beenden) -> ", 0, spiele.size()) - 1;
}

void SpielLaden_Speichern::ausgabe()
{
    std::vector<std::string> namen;

    for (int i = 0; i < spiele.size(); i++)
    {
        std::string ausgabe;
        std::stringstream sstr(spiele[i]);
        std::string temp;
        int anzahl;

        std::getline(sstr, temp, ';');
        ausgabe = '(' + std::to_string(i + 1) + ") " + temp + " -> ";
        sstr >> anzahl;
        sstr.ignore();
        for (int i = 0; i < anzahl; i++)
        {
            std::getline(sstr, temp, ';');
            ausgabe += temp;
            if(i < anzahl - 1)
            {
                ausgabe += ", ";
            }
        }
        namen.emplace_back(ausgabe);
    }

    std::string ueberschrift = "Vorhandene Spiele";
    std::string leer = "Keine Einträge";

    int laengsterString = ueberschrift.size() - anzahlUmlaute(ueberschrift);
    if (programm.size() > ueberschrift.size())
    {
        laengsterString = programm.size() - anzahlUmlaute(programm);
    }

    if (namen.empty() && laengsterString < leer.size())
    {
        laengsterString = leer.size();
    }

    for(const auto& element : namen )
    {
        if (laengsterString < element.size())
        {
            laengsterString = element.size();
        }
    }
    
    int mittelteil = laengsterString + 2;

    std::string e_LO = "+";//"┌";
    std::string e_RO = "+";//"┐";
    std::string e_LU = "+";//"└";
    std::string e_RU = "+";//"┘";
    char h    = '|';//'|';
    char v    = '-';//'-';
    
    system("clear");
    std::cout << std::string(2, '\n');
    if (!programm.empty())
    {
        std::cout << VERSCHIEBEN << e_LO << std::string(mittelteil, v) << e_RO << std::endl;
        std::cout << VERSCHIEBEN << h << std::string(mittelteil, ' ') << h << std::endl;
        std::cout << VERSCHIEBEN << h << textfeldZentriert(programm, mittelteil) << h << std::endl;
        std::cout << VERSCHIEBEN << h << std::string(mittelteil, ' ') << h << std::endl;
        std::cout << VERSCHIEBEN << h << std::string(mittelteil, v) << h << std::endl;
        std::cout << VERSCHIEBEN << h << textfeldZentriert("* " + ueberschrift + " *", mittelteil) << h << std::endl;
        std::cout << VERSCHIEBEN << h << std::string(mittelteil, ' ') << h << std::endl;
    }
    else
    {
        std::cout << VERSCHIEBEN << e_LO << std::string(mittelteil, v) << e_RO << std::endl;
        std::cout << VERSCHIEBEN << h << std::string(mittelteil, ' ') << h << std::endl;
        std::cout << VERSCHIEBEN << h << textfeldZentriert(ueberschrift, mittelteil) << h << std::endl;
        std::cout << VERSCHIEBEN << h << std::string(mittelteil, ' ') << h << std::endl;
        std::cout << VERSCHIEBEN << h << std::string(mittelteil, v) << h << std::endl;
    }
    
    int zaehler = 0;

    if (spiele.empty())
    {
        std::cout << VERSCHIEBEN << h << ' ' << std::left << std::setw((mittelteil - 2) + anzahlUmlaute(leer)) << leer << ' ' << h << std::endl;
        std::cout << VERSCHIEBEN << std::right << h << std::string(mittelteil, ' ') << h << std::endl;
    }
    
    for(auto it = namen.begin(); it != namen.end(); ++it)
    {
        std::cout << VERSCHIEBEN << h << ' ' << std::left << std::setw((mittelteil - 2) + anzahlUmlaute(*it)) << *it << ' ' << h << std::endl;
        std::cout << VERSCHIEBEN << std::right << h << std::string(mittelteil, ' ') << h << std::endl;
        if (++zaehler == 10)
        {
            break;
        }
    }
    
    std::cout << VERSCHIEBEN << e_LU << std::string(mittelteil, v) << e_RU << std::string(2, '\n');
}
