#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "spiel.hpp"
#include "bestenliste.hpp"
#include "eigeneBib.hpp"
#include "terminalBund.hpp"
#include "Spiel_Laden_Speichern.hpp"

#define VERSCHIEBEN std::string(1, '\t')

class Menuepunkte
{
    std::string menueText;
    int auswahl;

    public:
        Menuepunkte();
        Menuepunkte(const std::string& menueText, int auswahl);

        std::string print() const;
};

class Menue
{   
    enum Hauptmenue
    {
        BEENDEN,
        NEUES_SPIEL,
        HIGHSCORE,
        SPIEL_LADEN,
        PRAESENTATION,
        HAUPT
    };

    std::string programmname;
    std::string dateiBestenliste;
    std::string dateiSpieldaten;
    std::string dateiHtml;

    std::vector<Menuepunkte> hauptMenu{{"Neues Spiel", Hauptmenue::NEUES_SPIEL},
                                       {"Highscore", Hauptmenue::HIGHSCORE},
                                       {"Spiel laden", Hauptmenue::SPIEL_LADEN},
                                       {"Projektpräsentation", Hauptmenue::PRAESENTATION},
                                       {"Ende", Hauptmenue::BEENDEN}};

    void gehtNochNicht() const;
    void menueAusgabe(std::string ueberschrift, int welchesMenue) const;
    
    void neuesSpiel();
    void ladenSpiel();
    
    public:
        Menue(const std::string& programmname, const std::string& pfad);

        int menue();
        
};





