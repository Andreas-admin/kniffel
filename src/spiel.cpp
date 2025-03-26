#include "../include/spiel.hpp"

Spiel::Spiel(bool laden)
{
    if (!laden)
    {
        int anzahl = abfrageIntZahl("Bitte Anzahl Spieler angeben -> ", 1, 6);
        for (int i = 0; i < anzahl; i++)
        {
            spieler.emplace_back(new Spieler(abfrageText("Bitte Namen eingeben -> ")));
        }
    }
}

Spiel::~Spiel()
{
    for(auto& e : spieler)
    {
        delete e;
    }
}

std::pair<bool, bool> Spiel::spielen(bool geladen)
{
    Block block{spieler};
    std::map<std::string, int> map;
    std::pair<bool, bool> beendenSpeichern{false, false};

    if (!geladen)
    {
        indexS = 0;
        indexR = 1;
    }
    
    do
    {
        do
        {
            beendenSpeichern = aktion.rundeKomplett(spieler[indexS], becher, block);
            if (beendenSpeichern.first)
            {
                return beendenSpeichern;
            }

            indexS++;
        } while (indexS < spieler.size());

        indexS = 0;
        indexR++;

    } while (indexR <= 13);
    
    indexS = aktion.gewonnenHat(spieler);

    system("clear");
    block.ausgabe();
    std::cout << std::endl << VERSCHIEBEN << "Gewonnen hat " << spieler[indexS]->getFarbe() << spieler[indexS]->getName() << RESET 
              << " mit " << spieler[indexS]->getFarbe() << spieler[indexS]->getGesamtPunkte() << RESET
              << " Punkten." << std::endl << std::endl;

    for (const auto& e : spieler)
    {
        map[e->getName()] = e->getGesamtPunkte();
    }
    
    dummyEingabe();
    return beendenSpeichern;
}

std::map<std::string, int> Spiel::getPunkteSpieler() const
{
    std::map<std::string, int> map;

    for (const auto& e : spieler)
    {
        map[e->getName()] = e->getGesamtPunkte();
    }
    
    return map;
}

int Spiel::getAnzahlSpieler() const
{
    return spieler.size();
}

const std::vector<Spieler*> Spiel::getSpieler() const
{
    return spieler;
}

void Spiel::setSpieler(const std::string& name)
{
    spieler.emplace_back(new Spieler(name));
}

int Spiel::getIndexSpieler() const
{
    return indexS;
}

int Spiel::getIndexRunde() const
{
    return indexR;
}

void Spiel::setIndexSpieler(int i)
{
    indexS = i;
}

void Spiel::setIndexRunde(int i)
{
    indexR = i;
}