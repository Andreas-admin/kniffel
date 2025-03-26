#include "../include/kniffelblock.hpp"

Block::Block(const std::vector<Spieler*>& namen)
{
    initErste();
    initLetzte();
    tabelle.emplace_back(&ersteSpalte);
    for (size_t i = 0; i < namen.size(); i++)
    {
        tabelle.emplace_back(namen[i]->getSpalte());
        farben.emplace_back(namen[i]->getFarbe());
    }
    tabelle.emplace_back(&letzteSpalte);

    initTrennung();
}

void Block::initErste()
{
    int groesse = 23;

    ersteSpalte.reserve(20);

    ersteSpalte.emplace_back(textfeldZentriert("Spiel", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("1 -> Einer ", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("2 -> Zweier", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("3 -> Dreier", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("4 -> Vierer", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("5 -> Fünfer", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("6 -> Sechser", groesse));

    ersteSpalte.emplace_back(textfeldZentriert("Summe", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("Bonus", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("Gesamt Oben", groesse));

    ersteSpalte.emplace_back(textfeldZentriert(" 7 -> Dreierpasch  ", groesse));
    ersteSpalte.emplace_back(textfeldZentriert(" 8 -> Viererpasch  ", groesse));
    ersteSpalte.emplace_back(textfeldZentriert(" 9 -> Full House   ", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("10 -> Kleine Straße", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("11 -> Große Straße", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("12 -> Kniffel      ", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("13 -> Chance       ", groesse));

    ersteSpalte.emplace_back(textfeldZentriert("Summe Unten", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("Summe Oben ", groesse));
    ersteSpalte.emplace_back(textfeldZentriert("Gesamtsumme", groesse));
}

void Block::initLetzte()
{
    int groesse = 45;

    letzteSpalte.reserve(20);

    letzteSpalte.emplace_back(textfeldZentriert("Hinweis", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Nur Einer   zählen", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Nur Zweier  zählen", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Nur Dreier  zählen", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Nur Vierer  zählen", groesse));
    letzteSpalte.emplace_back(textfeldZentriert(" Nur Fünfer  zählen", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Nur Sechser zählen", groesse));

    letzteSpalte.emplace_back(textfeldZentriert(" ", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("35 Punkte, wenn oben min. 63 Punkte", groesse));
    letzteSpalte.emplace_back(textfeldZentriert(" ", groesse));

    letzteSpalte.emplace_back(textfeldZentriert(" Drei gleiche Zahlen – Alle Augen zählen", groesse));
    letzteSpalte.emplace_back(textfeldZentriert(" Vier gleiche Zahlen – Alle Augen zählen", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Drei gleiche und zwei gleiche, 25 Punkte ", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Vier zusammenhängend – 30 Punkte", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Fünf zusammenhängend – 40 Punkte", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Fünf gleiche - 50 Punkte", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Alle Augen zählen", groesse));
    
    letzteSpalte.emplace_back(textfeldZentriert("Summe Unten", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Summe Oben ", groesse));
    letzteSpalte.emplace_back(textfeldZentriert("Gesamtsumme", groesse));
}

void Block::initTrennung()
{
    trennung = '+' + std::string(23, '-') + '+';
    
    for (size_t i = 1; i < tabelle.size() - 1; i++)
    {
        int umlaut = anzahlUmlaute((*tabelle[i])[0]);
        
        trennung += std::string((*tabelle[i])[0].size() - umlaut, '-') + '+';
    }

    trennung += std::string(45, '-') + '+';
}

void Block::ausgabe() const
{
    std::cout << std::endl << std::endl << VERSCHIEBEN << trennung << std::endl;

    for (int i = 0; i < 20; i++)
    {
        std::cout << VERSCHIEBEN << '|';
        for (int j = 0; j < tabelle.size(); j++)
        {
            if ((j > 0 && i == 0) && (j < tabelle.size() - 1 && i == 0))
            {
                std::cout << farben[j - 1] << (*tabelle[j])[i] << RESET << '|';
            }
            else
            {
                std::cout << (*tabelle[j])[i] << '|';
            }
        }

        if (i == 0 || i == 6 || i == 9 || i == 16 || i == 19)
        {
            std::cout<< std::endl << VERSCHIEBEN << trennung << std::endl;
        }
        else
        {
            std::cout<< std::endl;
        }
    }
}

