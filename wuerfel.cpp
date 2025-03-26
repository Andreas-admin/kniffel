#include "../include/wuerfel.hpp"

//------------------------------- Wuerfel ------------------------------------------------

Wuerfel::Wuerfel() : wert(1), gesperrt(false){}

int Wuerfel::getWert() const{return wert;}

bool Wuerfel::getGesperrt() const{return gesperrt;}

void Wuerfel::wuerfelSperren()
{
    gesperrt = true;
}

void Wuerfel::wuerfelEntsperren()
{
    gesperrt = false;
}

void Wuerfel::wuerfeln(bool anzeigen)
{
    wert = zufallZahl(1, 6);

    if(anzeigen)
    {
        int index = 0;
        do
        {
            std::cout << zufallZahl(1, 6) << std::flush;
            
            std::this_thread::sleep_for (std::chrono::milliseconds(50));
            std::cout << '\r' << std::string(10, ' ') << '\r' << VERSCHIEBEN;
            index++;
            
        } while (index < 30);
        std::cout << VERSCHIEBEN << wert << std::endl;
    }
}

//------------------------------- Wuerfelbecher ------------------------------------------------

Wuerfelbecher::Wuerfelbecher(int anzahl)
{
    wuerfel.reserve(anzahl);
    for (size_t i = 0; i < anzahl; i++)
    {
        wuerfel.emplace_back(new Wuerfel());
    }

    anzeigeKopf  =        VERSCHIEBEN + "+-------------------+" + '\n';
    anzeigeKopf +=        VERSCHIEBEN + "| A | B | C | D | E |" + '\n';
    anzeigeKopf +=        VERSCHIEBEN + "+-------------------+" + '\n';
    anzeigeKopf +=        VERSCHIEBEN + '|';

    anzeigeEnde  = '\n' + VERSCHIEBEN + "+-------------------+" + '\n';
}

Wuerfelbecher::~Wuerfelbecher()
{
    for(auto& e : wuerfel)
    {
        delete e;
        e = nullptr;
    }
}

const std::vector<Wuerfel*>& Wuerfelbecher::getWuerfel() const {return wuerfel;}

void Wuerfelbecher::wuerfelnBecher()
{
    int index = 0;

    for (size_t i = 0; i < wuerfel.size(); i++)
    {
        if (!wuerfel[i]->getGesperrt())
        {
             wuerfel[i]->wuerfeln(false);
        }
    }

    std::cout << anzeigeKopf;

    do
    {
        for (size_t i = 0; i < wuerfel.size(); i++)
        {
            if (wuerfel[i]->getGesperrt())
            {
                std::cout << BG_GREEN << " " << wuerfel[i]->getWert() << " " << RESET << "|" << std::flush;// BGREEN
            }
            else
            {
                std::cout << " " << zufallZahl(1, 6) << " |" << std::flush;
            }
            
        }

        std::this_thread::sleep_for (std::chrono::milliseconds(50));
        std::cout << '\r' << std::string(100, ' ') << '\r' << VERSCHIEBEN << '|';
        index++;

    } while (index < 30);

    for (size_t i = 0; i < wuerfel.size(); i++)
    {
        std::cout << (wuerfel[i]->getGesperrt() ? BG_GREEN : BWHITE) << " " << wuerfel[i]->getWert() << " " << RESET << "|";
    }

    std::cout << anzeigeEnde;
}

void Wuerfelbecher::wuerfelAendern(int index)
{
    if(wuerfel[index]->getGesperrt())
    {
        wuerfel[index]->wuerfelEntsperren();
    }
    else
    {
        wuerfel[index]->wuerfelSperren();
    }
}

void Wuerfelbecher::alleSperren()
{
    for (auto& w : wuerfel)
    {
        w->wuerfelSperren();
    }
}

void Wuerfelbecher::alleEntsperren()
{
    for (auto& w : wuerfel)
    {
        w->wuerfelEntsperren();
    }
}

bool Wuerfelbecher::alleGesperrt() const
{
    for(const auto& e : wuerfel)
    {
        if (!(e->getGesperrt()))
        {
            return false;
        }
    }
    return true;
}

void Wuerfelbecher::ausgabe(bool ergebnis) const
{
    std::cout << anzeigeKopf;

    for (size_t i = 0; i < wuerfel.size(); i++)
    {
        if (ergebnis)
        {
            std::cout << BG_BGREEN << " " << wuerfel[i]->getWert() << " " << RESET << "|";
        }
        else
        {
            std::cout << (wuerfel[i]->getGesperrt() ? BG_BGREEN : BWHITE) << " " << wuerfel[i]->getWert() << " " << RESET << "|";
        }
    }

    std::cout << anzeigeEnde;
}
