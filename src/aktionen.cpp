//#include "../include/aktionen.hpp"
#include "../include/aktionen.hpp"

std::pair<bool, bool> Aktion::rundeKomplett(Spieler* spieler, Wuerfelbecher& becher, Block& b)
{
    std::pair<bool, bool> beendenSpeichern{false, false};

    for (int i = 0; i < 3; i++)
    {
        system("clear");
        b.ausgabe();
        std::cout << VERSCHIEBEN << spieler->getFarbe() << spieler->getName() << RESET << " ist an der Reihe." << std::endl;
        if (i == 0)
        {
            char tmp = abfrageChar("Würfeln mit W - Beenden mit B -> ", 'B');
            tmp = toupper(tmp);
            if (tmp == 'B')
            {
                beendenSpeichern.first = true;
                beendenSpeichern.second = abfrageIntZahl("Möchtest du das Spiel speichern (1)ja/(0)nein -> ", 0, 1);
                return beendenSpeichern;  
            }
        }
        
        if (!(becher.alleGesperrt()))
        {
            std::cout << VERSCHIEBEN << "Runde " << i + 1 << ":\n";
            becher.wuerfelnBecher();
            if (i < 2)
            {
                do
                {
                    system("clear");
                    b.ausgabe();
                    std::cout << VERSCHIEBEN << spieler->getFarbe() << spieler->getName() << RESET << " ist an der Reihe." << std::endl;
                    std::cout << VERSCHIEBEN << "Runde " << i + 1 << ":\n";
                    becher.ausgabe();
                } while (!(wuerfelAbfrage(becher)));
            }
        }
    }

    system("clear");
    b.ausgabe();
    std::cout << VERSCHIEBEN << spieler->getFarbe() << spieler->getName() << RESET << " ist an der Reihe." << std::endl;
    becher.ausgabe(true);

    ergebnisEintragen(spieler, becher);

    becher.alleEntsperren();
    return beendenSpeichern;;
}

bool Aktion::wuerfelAbfrage(Wuerfelbecher& becher)
{
    char eingabe;
    bool fertig = false;

    eingabe = abfrageChar("Welche Würfel möchtest du bearbeiten Würfeln (grün -> gesperrt , weiß -> wird weiter gewürfelt)?\n" 
                          + VERSCHIEBEN + "(z.B A -> für A, X -> weiter Würfeln, Y -> alle) -> ", 'X');
    eingabe = toupper(eingabe);
    switch (eingabe)
    {
    case 'A':
        becher.wuerfelAendern(0);
        break;
    case 'B':
        becher.wuerfelAendern(1);
        break;
    case 'C':
        becher.wuerfelAendern(2);
        break;
    case 'D':
        becher.wuerfelAendern(3);
        break;
    case 'E':
        becher.wuerfelAendern(4);
        break;
    case 'X':
        fertig = true;
        break;
    case 'Y':
        do
        {
            eingabe = abfrageChar("(E) alle weiter würfeln, (S) keinen weiter würfeln -> ", '#');
            eingabe = toupper(eingabe);
            if (eingabe != 'E' && eingabe != 'S')
            {
                std::cout << VERSCHIEBEN << "Ungültige Eingabe!!!\n";
            }
        } while (eingabe != 'E' && eingabe != 'S');
        
        if (eingabe == 'E')
        {
            becher.alleEntsperren();
        }
        else
        {
            becher.alleSperren();
        }
        break;
    default:
        std::cout << VERSCHIEBEN << "Fehleingabe!!!\n";
        break;
    }
    
    return fertig;
}

void Aktion::ergebnisEintragen(Spieler* spieler, const Wuerfelbecher& becher) const
{
    int auswahl = auswahlMitPruefung(spieler);
    int ergebnis = 0;
    
    switch (auswahl)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        ergebnis = ergebnisObenChance(auswahl, becher);
        break;

    case DREIERPASCH:
    case VIERERPASCH:
        ergebnis = ergebnisPasch(auswahl, becher);
        break;

    case FULL_HOUSE:
        ergebnis = ergebnisFull(becher);
        break;

    case KLEINE_ST:
    case GROSSE_ST:
        ergebnis = ergebnisStrasse(auswahl, becher);
        break;

    case KNIFFEL:
        ergebnis = ergebnisPasch(auswahl, becher);
        break;

    case CHANCE:
        ergebnis = ergebnisObenChance(auswahl, becher);
        break;

    default:
        break;
    }

    spieler->punkteEintragen(ergebnis, (auswahl > 6 ? auswahl + 3 : auswahl));
}

int Aktion::ergebnisObenChance(int auswahl, const Wuerfelbecher& becher) const
{
    int ergebnis = 0;

    if (auswahl == CHANCE)
    {
        for(const auto& e : becher.getWuerfel())
        {
            ergebnis += e->getWert();
        }
        return ergebnis;
    }
    
    for(const auto& e : becher.getWuerfel())
    {
        if (e->getWert() == auswahl)
        {
            ergebnis += auswahl;
        } 
    }

    return ergebnis;
}

int Aktion::ergebnisPasch(int n, const Wuerfelbecher& becher) const
{
    int zaehler = 0;
    int ergebnis = 0;

    for (int i = 1; i <= 6; i++)
    {
        for(const auto& e : becher.getWuerfel())
        {
            if (e->getWert() == i)
            {
                zaehler++;
            } 
        }

        if (n == DREIERPASCH && zaehler >= 3)
        {
            for(const auto& e : becher.getWuerfel())
            {
                ergebnis += e->getWert();
            }
            break;
        }

        if (n == VIERERPASCH && zaehler >= 4)
        {
            for(const auto& e : becher.getWuerfel())
            {
                ergebnis += e->getWert();
            }
            break;
        }

        if (n == KNIFFEL && zaehler == 5)
        {
            ergebnis = 50;
            break;
        }
            
        zaehler = 0;
    }

    return ergebnis;
}

int Aktion::ergebnisFull(const Wuerfelbecher& becher) const
{
    std::set<int> s;

    int zaehler = 0;
    bool dreier, zweier;

    for (int i = 1; i <= 6; i++)
    {
        for(const auto& e : becher.getWuerfel())
        {
            if (e->getWert() == i)
            {
                zaehler++;
            } 
        }
        s.insert(zaehler);
        zaehler = 0;
    }

    dreier = *(s.rbegin()) == 3 ? true : false;
    if (dreier)
    {
        s.erase(*s.rbegin());
        zweier = *(s.rbegin()) == 2 ? true : false;
    }

    return ((dreier && zweier) ? 25 : 0);
}

int Aktion::ergebnisStrasse(int n, const Wuerfelbecher& becher) const
{
    std::vector<int> w;
    w.reserve(5);

    for (const auto& e : becher.getWuerfel())
    {
        w.push_back(e->getWert());
    }

    std::sort(w.begin(), w.end());

    int zaehler = 1;
    for (int i = 0; i < 5 - 1; i++)
    {
        if (w[i] + 1 == w[i + 1])
        {
            zaehler++;
        }
    }
    
    if (n == KLEINE_ST && zaehler >= 4)
    {
        return 30;
    }

    if (n == GROSSE_ST && zaehler > 4)
    {
        return 40;
    }
    
    return 0;
}

int Aktion::gewonnenHat(const std::vector<Spieler*>& spieler) const
{
    int index = 0;
    for(int i = 0; i < spieler.size(); i++)
    {
        if (spieler[i]->getGesamtPunkte() > spieler[index]->getGesamtPunkte())
        {
            index = i;
        }
    }

    return index;
}

int Aktion::auswahlMitPruefung(const Spieler* spieler) const
{
    int auswahl;
    do
    {
        auswahl = abfrageIntZahl("Wo möchtest du dein Ergebnis eintragen -> ", 1, 13);

        if (!(spieler->indexBelegt(auswahl > 6 ? auswahl + 3 : auswahl)))
        {
            return auswahl;
        }
        
        std::cout << VERSCHIEBEN << "An Stelle " << auswahl << " ist schon ein Eintrag!!!\n";
        
    }while (true);

    return -1;
}
