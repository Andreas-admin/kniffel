#pragma once

#include <vector>
#include <map>

#include "spieler.hpp"
#include "aktionen.hpp"
#include "kniffelblock.hpp"
#include "wuerfel.hpp"
#include "terminalBund.hpp"

#define VERSCHIEBEN std::string(1, '\t')

class Spiel
{
    std::vector<Spieler*> spieler;
    Wuerfelbecher becher;
    Aktion aktion;
    int indexS;
    int indexR;

    public:
        Spiel(bool laden = false);
        ~Spiel();

        std::pair<bool, bool> spielen(bool geladen = false);
        std::map<std::string, int> getPunkteSpieler() const;
        int getAnzahlSpieler() const;
        const std::vector<Spieler*> getSpieler() const;
        int getIndexSpieler() const;
        int getIndexRunde() const;

        void setSpieler(const std::string& name);
        void setIndexSpieler(int i);
        void setIndexRunde(int i);
};


