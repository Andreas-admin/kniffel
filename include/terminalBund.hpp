/*/
    Von Meik Mittwoch für die Fakultät73
*/

#pragma once

// Font Color normal
#define BLACK "\33[30m"
#define RED "\33[31m"
#define GREEN "\33[32m"
#define YELLOW "\33[33m"
#define BLUE "\33[34m"
#define MAGENTA "\33[35m"
#define CYAN "\33[36m"
#define WHITE "\33[37m"

// Font Color Bright
#define BBLACK "\33[90m"
#define BRED "\33[91m"
#define BGREEN "\33[92m"
#define BYELLOW "\33[93m"
#define BBLUE "\33[94m"
#define BMAGENTA "\33[95m"
#define BCYAN "\33[96m"
#define BWHITE "\33[97m"

// Background Color
#define BG_BLACK "\33[40m"
#define BG_RED "\33[41m"
#define BG_GREEN "\33[42m"
#define BG_YELLOW "\33[43m"
#define BG_BLUE "\33[44m"
#define BG_MAGENTA "\33[45m"
#define BG_CYAN "\33[46m"
#define BG_WHITE "\33[47m"

// Backround Color Bright
#define BG_BBLACK "\33[100m"
#define BG_BRED "\33[101m"
#define BG_BGREEN "\33[102m"
#define BG_BYELLOW "\33[103m"
#define BG_BBLUE "\33[104m"
#define BG_BMAGENTA "\33[105m"
#define BG_BCYAN "\33[106m"
#define BG_BWHITE "\33[107m"

// Reset Changed Colors
#define RESET "\33[0m"

// Clear Console
#define CLEAR "\033[2J\033[1;1H"

/*

    Usage :

    #include "colorterminal.h"
    std::cout << RED << "Hallo " << GREEN "Welt" << RESET << std::endl

*/