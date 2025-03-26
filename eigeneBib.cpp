#include "../include/eigeneBib.hpp"

int abfrageIntZahl(const std::string& frage)
{
    int zahl;
    
    std::cout << VERSCHIEBEN << frage;                                 // Ausgabe Frage
    
    while (!(std::cin >> zahl))                                        // Schleife bis Eingabe eine Zahl
    {
        std::cin.clear();                                              // Clear Fehlerstatus
        std::cin.ignore(LLONG_MAX, '\n');                              // Leere den Eingabe-Puffer
        std::cout << VERSCHIEBEN << "Ungültige Eingabe" << std::endl;
        std::cout << VERSCHIEBEN << frage;                              // Fehlermeldung wenn ungültig
    }
    std::cin.clear();                                  
    std::cin.ignore(LLONG_MAX, '\n');                   
    return zahl;
}

int abfrageIntZahl(const std::string& frage, int min, int max)
{
    int zahl;
    
    std::cout << VERSCHIEBEN << frage;                                  // Ausgabe Frage
    do
    {
        while (!(std::cin >> zahl))                                     // Schleife bis Eingabe eine Zahl
        {
            std::cin.clear();                                           // Clear Fehlerstatus
            std::cin.ignore(LLONG_MAX, '\n');                           // Leere den Eingabe-Puffer
            std::cout << VERSCHIEBEN << "Ungültige Eingabe\n" << frage; // Fehlermeldung wenn ungültig
        }
        if (zahl < min || zahl > max)                                   // Fehlermeldung wenn außerhalb Bereich
        {
            std::cout << VERSCHIEBEN << "Nur Zahlen von " << min << " bis " << max << std::endl<< VERSCHIEBEN << frage;
        }
    }while (zahl < min || zahl > max);                                  // Schleife Zahl im gültigen Bereich
    std::cin.clear();                                       
    std::cin.ignore(LLONG_MAX, '\n');                       
    return zahl;
}

double abfrageDoubleZahl(const std::string& frage)
{
    double zahl;
    std::string temp;
    bool kommaVorgekommen;
    bool keineZahl;
    
    std::cout << VERSCHIEBEN << frage;                                         // Frage wird ausgegeben
    
    do
    {
        kommaVorgekommen = false;
        keineZahl = false;
        std::getline(std::cin, temp);                                   // Eingabe wird in einem String gespeichert

        for (int i = 0; i < temp.size(); i++)                           // Eingabe wird Stelle für Stelle geprüft
        {       
            if ((temp[i] < '0' || temp[i] > '9'))                       // Wenn keine Zahl
            {   
                if (temp[i] == ',' && (!kommaVorgekommen))              // ist es ein Komma und kam noch keines
                {
                    temp[i] = '.';                                      // mach aus ',' einen '.'
                    kommaVorgekommen = true;                            // setz Komma auf vorhanden
                }
                else if (temp[i] == '.' && (!kommaVorgekommen))         // ist es ein Punkt und kam noch keiner
                {
                    kommaVorgekommen = true;                            // setzt Komma auf vorhanden
                }
                else                                                    // alles Andere 
                {
                    keineZahl = true;                                   // keineZahl auf true             
                    break;                                              // und For - Schleife unterbrechen
                }
            }
        }
        
        if (keineZahl)
        {
            std::cout << VERSCHIEBEN << "Ungültige Eingabe\n"<< VERSCHIEBEN << frage; // Ausgabe das es keine gültige Zahl ist
        }                                                               // und Wiederholung der Frage
        else
        {
            std::stringstream ss(temp);                                 // Eingabe in einen Stringstream             
            ss >> zahl;                                                 // aus diesem in Variable damit es ein double wird
        }
    } while (keineZahl); 

    return zahl;
}

std::string abfrageText(const std::string& frage)
{
    std::string temp;
    int auswahl;

    do
    {
        std::cout << VERSCHIEBEN << frage;
        std::getline(std::cin, temp);
        auswahl = abfrageIntZahl("Richtig geschrieben? (1)ja/(0)nein -> ");
        
    } while (auswahl != 1);
    
    return temp;
}

char abfrageChar(const std::string& frage, char bestaetigung)
{
    std::string temp, t;
    int auswahl;
    
    do
    {
        std::cout << VERSCHIEBEN << frage;
        std::getline(std::cin, temp);
        std::cin.clear();                                       

        if (bestaetigung == temp[0] || bestaetigung + 32 == temp[0])
        {
            t = "-> ";
            t += toupper(temp.front());
            t += " <- ";
            auswahl = abfrageIntZahl(VERSCHIEBEN + t + "Sicher? (1)ja/(0)nein -> ");
        }
    } while (auswahl != 1);
    
    return temp.front();
}

int zufallZahl(int min, int max)
{
    static auto ursprung = std::random_device{};
    static auto generator = std::mt19937{ursprung()};
    auto dist = std::uniform_int_distribution<int>{min, max};

    return dist(generator);
}

std::string stringKlein(const std::string& wort)
{
    std::string temp = "";
    for (int i = 0; i < wort.size(); i++)
    {
        temp += std::tolower(wort[i]);
    }
    return temp;
}

std::string stringGross(const std::string& wort)
{
    std::string temp = "";
    for (int i = 0; i < wort.size(); i++)
    {
        temp += std::toupper(wort[i]);
    }
    return temp;
}

std::string stringUmkehren(const std::string& str)
{
    std::string temp = "";
    for (int i = str.size() - 1; i >= 0; i--)
    {
        temp += str[i];
    }
    return temp;
}

bool datenSpeichern(const std::vector<std::string>& daten, const std::string& dateiname)
{
    std::ofstream ofs(dateiname);
    if (!ofs.is_open())
    {
        std::cerr << VERSCHIEBEN << "Datei konnte nicht geöffnet werden" << std::endl;
        return false;
    }

    for (const auto& element : daten)
    {
        ofs << element;
    }
    return true;
}

std::vector<std::string> datenLaden(const std::string& dateiname)
{
    std::vector<std::string> v1;
    std::ifstream ifs(dateiname);
    if (!ifs.is_open())
    {
        std::cerr << VERSCHIEBEN << "Datei konnte nicht geöffnet werden" << std::endl;
        v1.emplace_back("");
        return v1;
    }
    std::string zeile;
    while (std::getline(ifs, zeile))
    {
        v1.emplace_back(zeile);
    }
    return v1;
}

int zeilenZaehlen(const std::string& dateiname)
{
    std::ifstream ifs(dateiname);
    int zaehler = 0;

    if(!ifs.is_open())
    {
        return zaehler;
    }

    std::string zeile;     
    while(std::getline(ifs, zeile))
    {
        zaehler++;
    }
    return zaehler;
}

std::chrono::steady_clock::time_point zeitStoppen()
{
    return std::chrono::steady_clock::now();
}

std::chrono::steady_clock::rep gestoppteZeit(int auswahl, std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point ende)
{
    enum
    {NANO, MIKRO, MILLI, SEKUNDE};
    switch (auswahl)
    {
    case NANO:
        return std::chrono::duration_cast<std::chrono::nanoseconds>(ende - start).count();
        break;
    case MIKRO:
        return std::chrono::duration_cast<std::chrono::microseconds>(ende - start).count();
        break;
    case MILLI:
        return std::chrono::duration_cast<std::chrono::milliseconds>(ende - start).count();
        break;
    case SEKUNDE:
        return std::chrono::duration_cast<std::chrono::seconds>(ende - start).count();
        break;
    default:
        return 0;
        break;
    }
     
}

std::string textfeldZentriert(const std::string& text, int groesse)
{
    int zaehlerU = 0;
    int zaehlerE = 0;
    std::string textNeu = text;

    for (int i = 0; i < textNeu.size(); i++)
    {
        if (istUmlaut(textNeu[i]))
        {
            zaehlerU++;
            i++;
        }
    }
    
    for (int i = 0; i < textNeu.size(); i++)
    {
        if (istEuro(textNeu[i]))
        {
            zaehlerE += 2;
            i += 2;
        }
    }
    
    int versatz = (groesse - (text.size())) / 2;

    //std::string ersatz = std::string(versatz, ' ');
    std::string ersatz = std::string(versatz + zaehlerU + zaehlerE, ' ');
    textNeu.append(ersatz);
    if (text.size() + (versatz * 2) < groesse)
    {
        textNeu.insert(0, " ");
    }
    //ersatz = std::string(versatz + zaehlerU + zaehlerE, ' ');
    ersatz = std::string(versatz, ' ');
    textNeu.insert(0, ersatz);

    return textNeu;
}

bool istUmlaut(const char z)
{
    std::string temp = "äÄöÖüÜß";
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i] == z)
        {
            return true;
        }
    }
    return false;
}

bool istEuro(const char z)
{
    std::string temp = "€";
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i] == z)
        {
            return true;
        }
    }
    return false;
}

int anzahlUmlaute(const std::string& wort)
{
    int zaehlerU = 0;

    for (int i = 0; i < wort.size(); i++)
    {
        if (istUmlaut(wort[i]))
        {
            zaehlerU++;
            i++;
        }
    }
    return zaehlerU;
}

bool istBuchstabe(const char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

char charKlein(const char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return (c + 32);
    }
    return c;
}

void dummyEingabe()
{
    char temp;
    std::cout << VERSCHIEBEN << "Weiter mit 'w' -> ";
    std::cin >> temp;
    std::cin.clear();                                       
    std::cin.ignore(LLONG_MAX, '\n');
}