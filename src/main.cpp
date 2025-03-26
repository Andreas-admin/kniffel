#include <mach-o/dyld.h>
#include <limits.h>

#include "../include/menue.hpp"

/*
compilierbefehl -> g++ -Wall src/*.cpp -o bin/temp -std=c++20
starten -> bin/temp
*/
int main()
{
    char buf [PATH_MAX];
    uint32_t bufsize = PATH_MAX;
    std::string pfad;

    if(!_NSGetExecutablePath(buf, &bufsize))
    {
        pfad = buf;
        for (int i = 0; i < 2; i++)
        {
            pfad.erase(pfad.find_last_of("/"));
        }
    }

    Menue m{"Willkommen bei Kniffel", pfad};
    while(m.menue() != 0){}
 
    return 0;
}