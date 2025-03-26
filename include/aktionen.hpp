#pragma once

#include <string>
#include <set>

#include "eigeneBib.hpp"
#include "spieler.hpp"
#include "wuerfel.hpp"
#include "kniffelblock.hpp"

#define VERSCHIEBEN std::string(1, '\t')

class Aktion
{
    enum
    {
        DREIERPASCH = 7,
        VIERERPASCH,
        FULL_HOUSE,
        KLEINE_ST,
        GROSSE_ST,
        KNIFFEL,
        CHANCE
    };
    
    bool wuerfelAbfrage(Wuerfelbecher& becher);
    void ergebnisEintragen(Spieler* spieler, const Wuerfelbecher& becher) const;
    int auswahlMitPruefung(const Spieler* spieler) const;

    int ergebnisObenChance(int auswahl, const Wuerfelbecher& becher) const;
    int ergebnisPasch(int n, const Wuerfelbecher& becher) const;
    int ergebnisFull(const Wuerfelbecher& becher) const;
    int ergebnisStrasse(int n, const Wuerfelbecher& becher) const;

public:
    std::pair<bool, bool> rundeKomplett(Spieler* spieler, Wuerfelbecher& becher, Block& b);
    int gewonnenHat(const std::vector<Spieler*>& spieler) const;
};





