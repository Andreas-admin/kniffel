#pragma once

#include <string>
#include <vector>

#include "eigeneBib.hpp"
#include "terminalBund.hpp"

#define VERSCHIEBEN std::string(1, '\t')

class Spieler
{
    inline static int spielerzahl = 0;
    inline static std::vector<std::string> farben{BGREEN, BMAGENTA, BBLUE, BYELLOW, BCYAN, BRED};
    std::string name;
    std::vector<int> punkte;
    std::vector<std::string> spalte;
    int textFeld;
    std::string farbe;
    
    void pruefenOben();
    void pruefenUnten();
    void pruefenGesamt();

    public:
        Spieler(const std::string& name);
        ~Spieler();

        std::string getName() const;
        std::string getFarbe() const;
        int getGesamtPunkte() const;
        bool indexBelegt(int index) const;

        void punkteEintragen(int p, int index);
        std::vector<std::string>* getSpalte();
        int getPunkte(int index) const;
};