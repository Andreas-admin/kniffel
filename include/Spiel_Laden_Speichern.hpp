#pragma once

#include "spiel.hpp"
#include "datum.hpp"

#define VERSCHIEBEN std::string(1, '\t')

//------------------------------- Spiel laden/speichern ------------------------------------------------

class SpielLaden_Speichern
{
    Spiel* const spiel;
    std::string dateiname;
    std::string programm;
    std::vector<std::string> spiele;
    int index;

    void spieleSpeichern() const;
    void spieleLaden();
    void auswahl();
    void ausgabe();
    
    public:
    SpielLaden_Speichern(Spiel* const spiel, const std::string& datei);
    SpielLaden_Speichern(Spiel* const spiel, const std::string& datei, const std::string& programm);
    ~SpielLaden_Speichern();
    void spielSpeichern(bool geladenes = false);
    bool spielLaden();
};
