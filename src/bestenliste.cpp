#include "../include/bestenliste.hpp"

Bestenliste::Eintrag::Eintrag(const std::string& name, int punkte) : name(name), punkte(punkte)
{
    datum.setDatum();
}

Bestenliste::Eintrag::Eintrag(const std::string& name, int punkte, Datum datum) : name(name), punkte(punkte), datum(datum){}

std::string Bestenliste::Eintrag::speichern() const
{
    return name + ',' + std::to_string(punkte) + ',' + datum.asString() + '\n';
}

std::string Bestenliste::Eintrag::anzeigen() const
{
    std::stringstream sstr;

    sstr << ' ' << datum.asString() << std::setw(6) << punkte << " : " << name;
    return sstr.str();
}

Bestenliste::Bestenliste(const std::string& programm, const std::string& dateiname) : programm(programm), dateiname(dateiname)
{
    laden();
}

Bestenliste::~Bestenliste()
{
    speichern();
}

void Bestenliste::laden()
{
    std::ifstream ifs(dateiname);
    if (!ifs.is_open())
    {
        return;
    }

    std::string zeile;
    std::string name;
    int punkte;
    int tag, monat, jahr;
    Datum datum;

    while (std::getline(ifs, zeile))
    {
        std::stringstream sstr(zeile);
        getline(sstr, name, ',');
        sstr >> punkte;
        sstr.ignore();
        sstr >> tag;
        sstr.ignore();
        sstr >> monat;
        sstr.ignore();
        sstr >> jahr;

        datum.setDatum(tag, monat, jahr);
        eintraege.emplace_back(name, punkte, datum);
    }
}

void Bestenliste::speichern() const
{
    std::ofstream ofs(dateiname);
    int zaehler = 0;
    for(auto it = eintraege.begin(); it != eintraege.end(); ++it)
    {
        ofs << it->speichern();

        if (++zaehler == 10)
        {
            break;
        }
    }
}

void Bestenliste::neuerEintrag(const std::string& name, int punkte)
{
    eintraege.emplace_back(name, punkte);
    std::sort(eintraege.begin(), eintraege.end(), [](Eintrag& a, Eintrag& b){return a.punkte > b.punkte;});
}

void Bestenliste::ausgeben() const
{
    std::string ueberschrift = "Bestenliste";
    std::string leer = "Keine Einträge";
    std::string e_LO = "+";//"┌";
    std::string e_RO = "+";//"┐";
    std::string e_LU = "+";//"└";
    std::string e_RU = "+";//"┘";
    char h    = '|';//'|';
    char v    = '-';//'-';


    int laengsterString = ueberschrift.size() - anzahlUmlaute(ueberschrift);
    if (programm.size() > ueberschrift.size())
    {
        laengsterString = programm.size() - anzahlUmlaute(programm);
    }

    if (eintraege.empty() && laengsterString < leer.size())
    {
        laengsterString = leer.size();
    }

    for(const auto& element : eintraege )
    {
        if (laengsterString < element.anzeigen().size())
        {
            laengsterString = element.anzeigen().size();
        }
    }
    
    int mittelteil = laengsterString + 2;
    
    system("clear");
    std::cout << std::string(2, '\n');
    if (programm != ueberschrift)
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
    
    //Punkte Listenmenü ausgeben
    int zaehler = 0;

    if (eintraege.empty())
    {
        std::cout << VERSCHIEBEN << h << ' ' << std::left << std::setw((mittelteil - 2) + anzahlUmlaute(leer)) << leer << ' ' << h << std::endl;
        std::cout << VERSCHIEBEN << std::right << h << std::string(mittelteil, ' ') << h << std::endl;
    }
    
    for(auto it = eintraege.begin(); it != eintraege.end(); ++it)
    {
        std::cout << VERSCHIEBEN << h << ' ' << std::left << std::setw((mittelteil - 2) + anzahlUmlaute(it->anzeigen())) << it->anzeigen() << ' ' << h << std::endl;
        std::cout << VERSCHIEBEN << std::right << h << std::string(mittelteil, ' ') << h << std::endl;
        if (++zaehler == 10)
        {
            break;
        }
    }
    
    std::cout << VERSCHIEBEN << e_LU << std::string(mittelteil, v) << e_RU << std::string(2, '\n');
}

