#pragma once

#include <iostream>
#include <vector>

#include "spieler.hpp"

#define RESET "\33[0m"

#define VERSCHIEBEN std::string(1, '\t')

class Block
{
    std::vector<std::vector<std::string>*> tabelle;
    std::vector<std::string> ersteSpalte;
    std::vector<std::string> letzteSpalte;
    std::string trennung;
    std::vector<std::string> farben;

    void initErste();
    void initLetzte();
    void initTrennung();

    public:
        Block(const std::vector<Spieler*>& namen);
        void ausgabe() const;
};