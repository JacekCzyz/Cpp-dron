#include <iostream>
#include <memory>
#include "../inc/Scena.hh"

dron &scena::wez_drona(int wybor)
{
    if (wybor == 2)
        return drony.back();
    return drony.front();
}
std::list<std::shared_ptr<bryla>> &scena::wez_liste()
{
    return przeszkody;
}