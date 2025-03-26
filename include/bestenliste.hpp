#pragma once

#include <fstream>

#include "datum.hpp"
#include "eigeneBib.hpp"

#define VERSCHIEBEN std::string(1, '\t')

class Bestenliste
{
    struct Eintrag
    {
        std::string name;
        int punkte;
        Datum datum;
        Eintrag(const std::string& name, int punkte);
        Eintrag(const std::string& name, int punkte, Datum datum);

        std::string speichern() const;
        std::string anzeigen() const;
    };

    std::vector<Eintrag> eintraege;
    std::string programm;
    std::string dateiname;

    void laden();
    void speichern() const;

    public:
    Bestenliste(const std::string& programm, const std::string& dateiname);
    ~Bestenliste();
    
    void ausgeben() const;
    void neuerEintrag(const std::string& name, int punkte);
};
