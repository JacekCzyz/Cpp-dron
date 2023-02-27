#ifndef GORA_DLUGA_GRAN_HH
#define GORA_DLUGA_GRAN_HH

#include <iostream>
#include <cmath>
#include <string>
#include "Bryla_geom.hh"

/*!
 * \file
 * \brief Plik zawiera definicje klasy gora z dluga grania
 */

/*!
 * \brief  klasa definiuje pojecie plaskowyzu
 *
 *  klasa posiada pole Wektor3D z jego lokacja, oraz string sluzacy do identyfikacji typu przeszkody
 *  ponadto posiada odpowiednie pola dziedziczone publicznie z klasy bryla
 */
class Gora_dluga_gran : public bryla
{
    Wektor3D lokalizacja;
    std::string identyfikator = "g";

public:
/*!
 * \brief  Konstruktory odpowienio inicjalizujace drona
 *
 *  lokalizacja zainicjowana zerami lub jesli podane sa argumenty, odpowiednimi wartosciami, ponadto inicjowane sa pola rodzica
 */
    Gora_dluga_gran(const char *plik_wynik, Wektor3D skala, Wektor3D pozycja) : bryla("bryly_wzorcowe/szescian_na_powierzchni.dat", plik_wynik, skala)
    {
        lokalizacja = pozycja;
        bool TworzGoreZDlugaGrania();
    }
    Gora_dluga_gran() : bryla()
    {
        lokalizacja = {0, 0, 0};
    }





/*!
 * \brief Tworzy bryłę reprezentującą górę z długą granią.
 *
 * Tworzy zapis na do plikuy bryły geometrycznej reprezentującej górę z
 * długą granią.
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
    bool TworzGoreZDlugaGraniastrm(std::istream &rStrmWej, std::ostream &rStrmWyj);

    

/*!
 * \brief Tworzy bryłę reprezentującą górę z długą granią.
 *
 * Tworzy zapis na strumieniu wierzchołków bryły geometrycznej reprezentującej górę z
 * długą granią.
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
    bool TworzGoreZDlugaGrania();

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