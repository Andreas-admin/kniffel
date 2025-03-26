#include "../include/spieler.hpp"

Spieler::Spieler(const std::string& name) : name(name)
{
    spalte.reserve(20);
    punkte.reserve(20);
    
    int umlaut = anzahlUmlaute(name);
    textFeld = name.size() + 2 - umlaut;

    spalte[0] = ' ' + name + ' ';
    punkte[0] = -1;
    
    for (int i = 1; i < 20; i++)
    {
        punkte[i] = -1;
        spalte[i] = std::string(textFeld, ' ');
    }
    farbe = farben[spielerzahl++];
}

Spieler::~Spieler(){spielerzahl--;}

std::string Spieler::getName() const {return name;}

std::string Spieler::getFarbe() const {return farbe;}

int Spieler::getGesamtPunkte() const {return punkte[19];}

int Spieler::getPunkte(int index) const
{
    return punkte[index];
}

bool Spieler::indexBelegt(int index) const { return punkte[index] > -1;}

void Spieler::punkteEintragen(int p, int index)
{
    punkte[index] = p;
    std::string text;
    
    if (p < 10)
    {
        if (p == 0)
        {
            text = " --";
        }
        else
        {
            text = "  " + std::to_string(p);
        }
    }
    else
    {
        if (p < 100)
        {
            text = " " + std::to_string(p);
        }
        else
        {
            text = std::to_string(p);
        }
    }
    
    spalte[index] = textfeldZentriert(text, textFeld);

    if (index <= 6)
    {
        if (punkte[18] == -1)
        {
            pruefenOben();
        }
    }

    if (index >= 10)
    {
        if (punkte[17] == -1)
        {
            pruefenUnten();
        }
    }
    
    if (punkte[19] == -1)
    {
        pruefenGesamt();
    }
}

std::vector<std::string>* Spieler::getSpalte(){return &spalte;}

void Spieler::pruefenOben()
{
    int sum = 0;
    for (int i = 1; i <= 6; i++)
    {
        if (punkte[i] == -1)
        {
            return;
        }

        sum += punkte[i];
    }

    this->punkteEintragen(sum, 7);

    this->punkteEintragen((sum > 62 ?  35 : 0), 8);

    this->punkteEintragen(punkte[7] + punkte[8], 9);

    this->punkteEintragen(punkte[9], 18);
}

void Spieler::pruefenUnten()
{
    int sum = 0;
    for (int i = 10; i <= 16; i++)
    {
        if (punkte[i] == -1)
        {
            return;
        }

        sum += punkte[i];
    }

    this->punkteEintragen(sum, 17);
}

void Spieler::pruefenGesamt()
{
    if (punkte[17] > -1 && punkte[18] > -1)
    {
        this->punkteEintragen(punkte[17] + punkte[18], 19);
    }
}
