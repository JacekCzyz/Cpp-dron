#ifndef GRANIASTOSLUP_HH
#define GRANIASTOSLUP_HH

#include <iostream>
#include <cmath>
#include "Bryla_geom.hh"

/*!
 * \file
 * \brief Plik zawiera definicje klasy graniastoslup
 */

/*!
 * \brief  klasa definiuje pojecie graniastoslupa
 *
 *  klasa posiada pole Wektor3D z jego lokacja, double z orientacja(kat w stopniach)
 *  ponadto posiada odpowiednie pola dziedziczone publicznie z klasy bryla
 */
class graniastoslup : public bryla
{
    Wektor3D lokalizacja;
    double orient;
    std::string identyfikator = "rotor";

public:
    /*!
 * \brief  Konstruktory odpowienio inicjalizujace drona
 *
 *  scena zainicjowana zerami lub jesli podane sa argumenty, odpowiednimi wartosciami, ponadto inicjowane sa pola rodzica
 */
    graniastoslup(const char *plik_wynik, Wektor3D skala, double kat, Wektor3D pozycja) : bryla("bryly_wzorcowe/graniastoslup6.dat", plik_wynik, skala)
    {
        orient = kat;
        lokalizacja = pozycja;
    }
    graniastoslup() : bryla()
    {
        lokalizacja = {0, 0, 0};
        orient = 0;
    }

    /*!
 * \brief  Funkcja tworzaca graniasotslup jako rotor drona
 *
 * W wyniku dzialania zwracana jest prawda/falsz, odpowiednie wartosci wpisywane do pliku zawierajacego wspolrzedne
 *  \param[in] plik_dron - plik do ktorego zapisuje sie wspolrzedne
 *  \param[in] KatObrotuRotora_st - kat orientacji rotora
 *  \param[in] trans - wektor o jaki przesuniety jest rotor wzgledem lokalnego ukladu wspolrzednych
 */

    void n_lok(Wektor3D nowa) { lokalizacja[0] = nowa[0]; lokalizacja[1] = nowa[1]; lokalizacja[2] = nowa[2]; }

    bool TworzRotor(const char *plik_dron, double KatObrotuRotora_st, Wektor3D trans);

    virtual bool czy_kolizja(Wektor3D centrum, double promien);

    virtual Wektor3D ret_lok() { return lokalizacja; }

    virtual std::string ret_ident() { return identyfikator; }
};

#endif