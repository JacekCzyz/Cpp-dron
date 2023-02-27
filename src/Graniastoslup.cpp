#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <string>
#include <unistd.h>
#include "../inc/Graniastoslup.hh"

using namespace std;

#define SKALA_ROTORA \
    {                \
        8, 8, 2      \
    }
#define SKALA_KORPUSU \
    {                 \
        10, 8, 4      \
    }
#define SKALA_JEDNOSTKOWA \
    {                     \
        1, 1, 1           \
    }

#define PLIK_WZORCOWEGO_GRANIASTOSLUPA6 "bryly_wzorcowe/graniastoslup6.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR1 "dat/PlikRoboczy_Dron1_Rotor1.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR2 "dat/PlikRoboczy_Dron1_Rotor2.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR3 "dat/PlikRoboczy_Dron1_Rotor3.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR4 "dat/PlikRoboczy_Dron1_Rotor4.dat"

#define PLIK_ROBOCZY__DRON2_ROTOR1 "dat/PlikRoboczy_Dron2_Rotor1.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR2 "dat/PlikRoboczy_Dron2_Rotor2.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR3 "dat/PlikRoboczy_Dron2_Rotor3.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR4 "dat/PlikRoboczy_Dron2_Rotor4.dat"

/*!
 * \brief Tworzy plik z wierzchołkami były modelującej rotor drona.
 *
 * Tworzy plik, w którym zostają zapise współrzędne wierzchołków
 * tworzących pojedynczy rotor drona. Zapisane one są w ten sposób, aby program gnuplot
 * mógł wyświetlić graniastosłubp Tworzona bryła zostaje obrócona
 * względem swojej pierwotnej orientacji o zadany kąt oraz przesunięta o wektor
 * translacji, którego współrzędne podane są jako parametry tej funkcji.
 *
 * \param[in] Plik_Rotor - nazwa pliku, w którym zostaną zapisane współrzędne
 *                                       wierzchołków bryły tworzącej rotor drona.
 * \param[in] KatObrotuRotora_st - kąt obrotu korpusu. Jego wartość wyrażona jest w stopniach.
 * \param[in] trans -  wektor translacji.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku.
 */
bool graniastoslup::TworzRotor(const char *Plik_Rotor, double KatObrotuRotora_st, Wektor3D trans)
{
    przeskaluj(SKALA_ROTORA);
    return TworzOpisPrzetranformowanejBryly(wez_wzor(), Plik_Rotor, KatObrotuRotora_st, trans);
    return false;
}

bool graniastoslup::czy_kolizja(Wektor3D centrum, double promien)
{
    Wektor3D dlugosci_skali = wez_skale();
    double odleglosc_srodkow = sqrt(pow((centrum[0] - lokalizacja[0]), 2) + pow((centrum[1] - lokalizacja[1]), 2)); //odleglosc miedzy srodkami okregu i graniastoslupa

    if (dlugosci_skali[0] > dlugosci_skali[1])
    {
        double promien_rzutu = dlugosci_skali[0] / 2;
        if ((promien + promien_rzutu) > odleglosc_srodkow)
            return true;
    }
    else
    {
        double promien_rzutu = dlugosci_skali[1] / 2;
        if ((promien + promien_rzutu) > odleglosc_srodkow)
            return true;
    }
    return false;
}