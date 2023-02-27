#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include <iostream>
#include <cmath>
#include "Bryla_geom.hh"
#define ILOSC_WIERZ_LINII_TWORZACEJ 4

/*!
 * \file
 * \brief Plik zawiera definicje klasy prostopadloscian
 */

/*!
 * \brief  klasa definiuje pojecie prostopadloscianu
 *
 *  klasa posiada pole Wektor3D z jego lokacja, double z orientacja(kat w stopniach)
 *  ponadto posiada odpowiednie pola dziedziczone publicznie z klasy bryla
 */
class prostopadloscian : public bryla
{
    Wektor3D lokalizacja;
    double orient;
    std::string identyfikator = "korpus";

public:
    /*!
 * \brief  Konstruktory odpowienio inicjalizujace prostopadlosican
 *
 *  scena zainicjowana zerami lub jesli podane sa argumenty, odpowiednimi wartosciami, ponadto inicjowane sa pola rodzica
 */
    prostopadloscian(const char *plik_wynik, Wektor3D skala, double kat, Wektor3D pozycja) : bryla("bryly_wzorcowe/szescian.dat", plik_wynik, skala)
    {
        orient = kat;
        lokalizacja = pozycja;
    }
    prostopadloscian() : bryla()
    {
        lokalizacja = {0, 0, 0};
        orient = 0;
    }

    /*!
 * \brief  Funkcja tworzaca prostopadloscian jako korpus drona
 *
 * W wyniku dzialania zwracana jest prawda/falsz, odpowiednie wartosci wpisywane do pliku zawierajacego wspolrzedne
 *  \param[in] plik_korpus - plik do ktorego zapisuje sie wspolrzedne
 *  \param[in] Kat_Obrotu_Korpusu_st - kat orientacji korpusu
 *  \param[in] trans - wektor o jaki przesuniety jest korpus wzgledem lokalnego ukladu wspolrzednych
 */

    void n_lok(Wektor3D nowa) { lokalizacja = nowa; }

    bool TworzKorpus(const char *plik_korpus,
                     double KatObrotuKorpusu_st,
                     Wektor3D trans);

    virtual bool czy_kolizja(Wektor3D centrum, double promien);

    virtual Wektor3D ret_lok() { return lokalizacja; }

    virtual std::string ret_ident() { return identyfikator; }
};

#endif