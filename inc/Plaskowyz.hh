#ifndef PLASKOWYZ_HH
#define PLASKOWYZ_HH

#include <iostream>
#include <cmath>
#include <string>
#include "Bryla_geom.hh"

/*!
 * \file
 * \brief Plik zawiera definicje klasy plaskowyz
 */

/*!
 * \brief  klasa definiuje pojecie plaskowyzu
 *
 *  klasa posiada pole Wektor3D z jego lokacja, oraz string sluzacy do identyfikacji typu przeszkody
 *  ponadto posiada odpowiednie pola dziedziczone publicznie z klasy bryla
 */
class Plaskowyz : public bryla
{
    Wektor3D lokalizacja;
    std::string identyfikator = "p";

public:
    /*!
 * \brief  Konstruktory odpowienio inicjalizujace plaskowyz
 *
 *  lokalizacja zainicjowana zerami lub jesli podane sa argumenty, odpowiednimi wartosciami, ponadto inicjowane sa pola rodzica
 */
    Plaskowyz(const char *plik_wynik, Wektor3D skala, Wektor3D pozycja) : bryla("bryly_wzorcowe/szescian_na_powierzchni.dat", plik_wynik, skala)
    {
        lokalizacja = pozycja;
        TworzPlaskowyz();
    }
    Plaskowyz() : bryla()
    {
        lokalizacja = {0, 0, 0};
    }



/*!
 * \brief Tworzy bryłę reprezentującą plaskowyz
 *
 * Tworzy zapis do pliku wierzchołków bryły geometrycznej reprezentującej plaskowyz
 *
 * \pre Strumień wejściowy jest otwarty do odczytu i zawiera zapis współrzędnych wierzchołków
 *      wzorcowego prostapadłościanu.
 *      Zapis ich jest zgodny z formatem pozwalającym poprawnie zwizualizować bryle
 *      przez program gnuplot.
 *
 * \param[in] rStrmWej - strumień wejściowy, który zawiera współrzędne
 *                                   wzorcowego prostopadłościanu.
 * \param[in] rStrmWej - strumień wyjściowy, do którego zostaną
 *                                   zapisane współrzędne wierzchołków przetransformowanego
 *                                   i odpowiednio zdeformowanego prostopadłościanu.
 * \retval true - plik z wierzcholkami nowej bryły reprezentującej górę z dlugą granią
 *                 został zapisany poprawnie.
 * \retval false - operacja nie powiodła się.
 */
    bool TworzPlaskowyz();


/*!
 * \brief Tworzy bryłę reprezentującą plaskowyz
 *
 * Tworzy zapis na strumieniu wierzchołków bryły geometrycznej reprezentującej plaskowyz
 *
 * \pre Strumień wejściowy jest otwarty do odczytu i zawiera zapis współrzędnych wierzchołków
 *      wzorcowego prostapadłościanu.
 *      Zapis ich jest zgodny z formatem pozwalającym poprawnie zwizualizować prostopadłościan
 *      przez program gnuplot.
 *
 * \param[in] rStrmWej - strumień wejściowy, który zawiera współrzędne
 *                                   wzorcowego prostopadłościanu.
 * \param[in] rStrmWej - strumień wyjściowy, do którego zostaną
 *                                   zapisane współrzędne wierzchołków przetransformowanego
 *                                   i odpowiednio zdeformowanego prostopadłościanu.
 * \retval true - plik z wierzcholkami nowej bryły reprezentującej górę z dlugą granią
 *                 został zapisany poprawnie.
 * \retval false - operacja nie powiodła się.
 */
    bool TworzPlaskowyzstrm(std::istream &rStrmWej, std::ostream &rStrmWyj);



/*!
 * \brief  funkcja zwracaja identyfikator przeszkody
 */
    virtual std::string ret_ident() { return identyfikator; }

/*!
 * \brief  funkcja zwracaja lokalizajce przeszkody
 */
    virtual Wektor3D ret_lok() { return lokalizacja; }

    virtual bool czy_kolizja(Wektor3D centrum, double promien);
};

#endif