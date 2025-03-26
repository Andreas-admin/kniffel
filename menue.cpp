#include "../include/menue.hpp"

//--------------------- Menuepunkte -------------------

Menuepunkte::Menuepunkte(){}
Menuepunkte::Menuepunkte(const std::string& menueText, int auswahl): menueText(menueText), auswahl(auswahl){}

std::string Menuepunkte::print() const
{
    return "< " + std::to_string(auswahl) + " > " + menueText;
}

//---------------------- Menue ----------------------------

Menue::Menue(const std::string& programmname, const std::string& pfad) : programmname(programmname)
{
    dateiBestenliste = pfad + "/build/bestenliste.csv";
    dateiSpieldaten  = pfad + "/build/spieldaten.csv";
    dateiHtml        = pfad + "/html/kniffel.html";
}

int Menue::menue()
{   
    //Punkte Hauptmenü ausgeben
    menueAusgabe("Hauptmenü", HAUPT);

    //Auswahl treffen
    int auswahl = abfrageIntZahl("Bitte wählen -> ", 0, hauptMenu.size() - 1);

    switch (auswahl)
    {
    case Hauptmenue::BEENDEN:
        std::cout << VERSCHIEBEN << "--> Programm beendet.\n";
        break;
    case Hauptmenue::NEUES_SPIEL:
        neuesSpiel();
        break;
    case Hauptmenue::HIGHSCORE:
        {
            Bestenliste bl(programmname, dateiBestenliste);
            system("clear");
            bl.ausgeben();
            dummyEingabe();
        }
        break;
    case Hauptmenue::SPIEL_LADEN:
        ladenSpiel();
        break;
    case Hauptmenue::PRAESENTATION:
        std::string tmp = "open " + dateiHtml;
        system(tmp.c_str());
        break;
    }
    return auswahl;
}

void Menue::gehtNochNicht() const
{
    std::cout << "Geht leider noch nicht" << std::endl;
}

void Menue::menueAusgabe(std::string ueberschrift, int welchesMenue) const
{
    std::string e_LO = "+";//"┌";
    std::string e_RO = "+";//"┐";
    std::string e_LU = "+";//"└";
    std::string e_RU = "+";//"┘";
    char h    = '|';//'|';
    char v    = '-';//'-';

    int laengsterString = ueberschrift.size() - anzahlUmlaute(ueberschrift);
    if (programmname.size() > ueberschrift.size())
    {
        laengsterString = programmname.size() - anzahlUmlaute(programmname);
    }
    
    const std::vector<Menuepunkte>* temp;

    switch (welchesMenue)
    {
    case HAUPT:
        temp = &hauptMenu;
        break;
    }

    for(const auto& element : *temp )
    {
        if (laengsterString < element.print().size())
        {
            laengsterString = element.print().size();
        }
    }
    
    int mittelteil = laengsterString + 2;

    system("clear");
    std::cout << std::string(2, '\n');
    std::cout << VERSCHIEBEN << e_LO << std::string(mittelteil, v) << e_RO << std::endl;
    std::cout << VERSCHIEBEN << h << std::string(mittelteil, ' ') << h << std::endl;
    std::cout << VERSCHIEBEN << h << textfeldZentriert(programmname, mittelteil) << h << std::endl;
    std::cout << VERSCHIEBEN << h << std::string(mittelteil, ' ') << h << std::endl;
    std::cout << VERSCHIEBEN << h << std::string(mittelteil, v) << h << std::endl;

    std::cout << VERSCHIEBEN << h << textfeldZentriert("* " + ueberschrift + " *", mittelteil) << h << std::endl;
    std::cout << VERSCHIEBEN << h << std::string(mittelteil, ' ') << h << std::endl;
    //Punkte Listenmenü ausgeben
    for(const auto& element : *temp )
    {
        std::cout << VERSCHIEBEN << h << ' ' << std::left << std::setw((mittelteil - 2) + anzahlUmlaute(element.print())) << element.print() << ' ' << h << std::endl;
    }
    std::cout << VERSCHIEBEN << std::right << h << std::string(mittelteil, ' ') << h << std::endl;
    std::cout << VERSCHIEBEN << e_LU << std::string(mittelteil, v) << e_RU << std::string(2, '\n');
}

void Menue::neuesSpiel()
{
    Spiel s{};
    std::pair<bool, bool> speichern = s.spielen();
    
    if (speichern.second)
    {
        SpielLaden_Speichern speichernLaden{&s, dateiSpieldaten};
        speichernLaden.spielSpeichern();
    }
    
    if (!speichern.first)
    {
        std::map<std::string, int> spieler = s.getPunkteSpieler();
        for (const auto& e : spieler)
        {
            Bestenliste bl(programmname, dateiBestenliste);
            bl.neuerEintrag(e.first, e.second);
        }
    }
}

void Menue::ladenSpiel()
{
    Spiel s{true};
    SpielLaden_Speichern speichernLaden{&s, dateiSpieldaten, programmname};
    
    if (speichernLaden.spielLaden())
    {
            std::pair<bool, bool> speichern = s.spielen(true);
    
        if (speichern.second)
        {
            speichernLaden.spielSpeichern(true);
        }
        
        if (!speichern.first)
        {
            std::map<std::string, int> spieler = s.getPunkteSpieler();
            for (const auto& e : spieler)
            {
                Bestenliste bl(programmname, dateiBestenliste);
                bl.neuerEintrag(e.first, e.second);
            }
        }
    }
}