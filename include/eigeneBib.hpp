#pragma once

#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

#define VERSCHIEBEN std::string(1, '\t')

/// @brief Nutzerabfrage nach einem int 
/// @param frage z.b "Bitte Zahl eingeben: "
/// @return Eingegebene Zahl
int abfrageIntZahl(const std::string& frage);

/// @brief Nutzerabfrage nach einem int, in einem gültigen Bereich ist.
/// @param frage z.b "Bitte Zahl eingeben: "
/// @param min   untere Grenze
/// @param max   obere Grenze
/// @return      Eingegebene Zahl
int abfrageIntZahl(const std::string& frage, int min, int max);

/// @brief Nutzerabfrage nach einem double,
/// ein ',' wird in '.' umgewandelt
/// @param frage z.b "Bitte Double Zahl eingeben: "
/// @return      Eingegebene Zahl
double abfrageDoubleZahl(const std::string& frage);

/// @brief Nutzerabfrage nach einem Text
/// @param frage die übergebene Frage an den Nutzer
/// @return Antwort als String
std::string abfrageText(const std::string& frage);

char abfrageChar(const std::string& frage, char bestaetigung);

/// @brief Zufallszahl von ... bis ...
/// @param min untere Grenze
/// @param max obere Grenze
/// @return    eine Zufällige Zahl aus dem Bereich
int zufallZahl(int min, int max);

/// @brief wandelt alle Buchstaben in Kleinbuchstaben um
/// @param wort String der umgewandelt werden soll
/// @return neuer String
std::string stringKlein(const std::string& wort);

/// @brief wandelt alle Buchstaben in Großbuchstaben um
/// @param wort String der umgewandelt werden soll
/// @return neuer String
std::string stringGross(const std::string& wort);

/// @brief gibt einen String rückwärts zurück
/// @param temp String der umgewandelt werden soll
/// @return neuer String
std::string stringUmkehren(const std::string& temp);

/// @brief speichert Daten aus einem Vector(jedes Element ist eine Zeile)
/// @param daten Vector der zu speichernden Daten
/// @param dateiname Dateiname wohin gespeichert wird
/// @return  true oder false (hat geklappt oder nicht)
bool datenSpeichern(const std::vector<std::string>& daten, const std::string& dateiname);

/// @brief läd Daten aus einer Datei und gibt einen Vector zurück
/// @param dateiname Dateiname aus der geladen werden soll
/// @return Vector(jedes Element ist eine Zeile)
std::vector<std::string> datenLaden(const std::string& dateiname);

/// @brief zählt die Zeilen aus einer .csv/.txt Datei
/// @param dateiname aus welcher gezählt werden soll
/// @return Anzahl der Zeilen(Einträge)
int zeilenZaehlen(const std::string& dateiname);

/// @brief Zeitpunkt
/// @return Aktueller Zeitpunkt
std::chrono::steady_clock::time_point zeitStoppen();

/// @brief Differenz von einem Startzeitpunkt und einem Endzeitpunkt
/// @param auswahl (0 -> Nanosekunden | 1 -> Mikrosekunden | 2 -> Millisekunden | 3 -> Sekunden)
/// @param start Startzeitpunkt
/// @param ende Endzeitpunkt
/// @return Differenz
std::chrono::steady_clock::rep gestoppteZeit(int auswahl, std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point ende);

/// @brief "Zentriert" einen Text in einem vorgegebenen Feld
/// @param text Text der zentriert werden soll
/// @param groesse Größe des Textfeldes
/// @return "Textfeld" als String
std::string textfeldZentriert(const std::string& text, int groesse);

/// @brief Zählt die Umlaute in einem String
/// @param wort String der untersucht werden soll
/// @return anzahl der Umlaute
int anzahlUmlaute(const std::string& wort);

/// @brief prüft ein Zeichen ob es ein Umlaut ist
/// @param z Zeichen das geprüft werden soll
/// @return Wahr oder Falsch
bool istUmlaut(const char z);

/// @brief prüft ein Zeichen ob es ein € Zeichen ist
/// @param z Zeichen das geprüft werden soll
/// @return Wahr oder Falsch
bool istEuro(const char z);

bool istBuchstabe(const char c);

char charKlein(const char c);

void dummyEingabe();