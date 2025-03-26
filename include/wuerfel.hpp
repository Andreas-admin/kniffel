#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <thread>

#include "eigeneBib.hpp"
#include "terminalBund.hpp"

#define VERSCHIEBEN std::string(1, '\t')

class Wuerfel
{
    int  wert;
    bool gesperrt;

    public:
        Wuerfel();
        int getWert() const;
        bool getGesperrt() const;
        
        void wuerfelSperren();
        void wuerfelEntsperren();
        void wuerfeln(bool anzeigen = true);
};

class Wuerfelbecher
{
    std::vector<Wuerfel*> wuerfel;
    std::string anzeigeKopf;
    std::string anzeigeEnde;

    public:
        Wuerfelbecher(int anzahl = 5);
        ~Wuerfelbecher();

        const std::vector<Wuerfel*>& getWuerfel() const;
        bool alleGesperrt() const;
        
        void wuerfelnBecher();
        void wuerfelAendern(int index);
        void alleSperren();
        void alleEntsperren();
        void ausgabe(bool ergebnis = false) const;
};