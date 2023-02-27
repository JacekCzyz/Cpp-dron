#include "../inc/Gora_Ostry_Szczyt.hh"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <string>
#include <unistd.h>
using namespace std;

/*!
 * \brief Tworzy bryłę reprezentującą górę z ostrym wierzchołkiem.
 *
 * Tworzy zapis wierzchołków bryły geometrycznej reprezentującej górę z
 * ostrym wierzchołkiem.
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
 * \retval true - plik z wierzcholkami nowej bryły reprezentującej górę z ostrym szczytem
 *                 został zapisany poprawnie.
 * \retval false - operacja nie powiodła się.
 */
bool Gora_ostry::TworzGoreZOstrymSzczytemstrm(istream &rStrmWej, ostream &rStrmWyj)
{
    assert(rStrmWej.good());
    assert(rStrmWyj.good());

    Wektor3D Wierz;

    for (unsigned int Ind_krawedz = 0; Ind_krawedz < 5; ++Ind_krawedz)
    {
        for (unsigned int Ind_wierz = 0; Ind_wierz < 4; ++Ind_wierz)
        {
            rStrmWej >> Wierz;
            if (rStrmWej.fail())
                return false;

            if (Wierz[2] > 0.5)
            { // Tutaj realizowana jest deformacja
                Wierz[0] = Wierz[1] = 0;
            }
            else if (Wierz[2] == 0.5)
            {
                Wierz[0] /= 2;
                Wierz[1] /= 2;
            }

            TransformujWierzcholek(Wierz, lokalizacja);

            rStrmWyj << Wierz;
            //  << endl;
            if (rStrmWyj.fail())
                return false;
        }
        rStrmWyj << endl; // Dodatkowa linia oddzielająca krawędzie
    }
    return !rStrmWyj.fail();
}

/*!
 * Tworzy zapis wierzchołków bryły geometrycznej reprezentującej górę z
 * ostrym wierzchołkiem.
 *
 * \pre Plik wzorcowy zawiera zapis współrzędnych wierzchołków wzorcowego prostapadłościanu.
 *      Zapis ich jest zgodny z formatem pozwalającym poprawnie zwizualizować prostopadłościan
 *      przez program gnuplot.
 *
 * \param[in] sNazwaPlikuWzorcowego - nazwa pliku, który zawiera współrzędne
 *                                   wzorcowego prostopadłościanu.
 * \param[in] Skala_x - wartość współczynnika skalowania współrzędnych wzdłuż osi OX.
 * \param[in] Skala_y - wartość współczynnika skalowania współrzędnych wzdłuż osi OY.
 * \param[in] Skala_z - wartość współczynnika skalowania współrzędnych wzdłuż osi OZ.
 * \param[in] Polozenie_x - współrzędna x-owa docelowego położenia tworzonej góry.
 * \param[in] Polozenie_y - współrzędna y-owa docelowego położenia tworzonej góry.
 * \param[in] Polozenie_z - współrzędna z-owa docelowego położenia tworzonej góry.
 * \param[in] sNazwaPlikuFinalnego - nazwa pliku finalnego, do którego zostaną
 *                                   zapisane współrzędne wierzchołków przetransformowanego
 *                                   i odpowiednio zdeformowanego prostopadłościanu.
 * \retval true - plik z wierzcholkami nowej bryły reprezentującej górę z ostrym szczytem
 *                 został zapisany poprawnie.
 * \retval false - operacja nie powiodła się.
 */
bool Gora_ostry::TworzGoreZOstrymSzczytem()
{
    ifstream StrmWej(wez_wzor());
    ofstream StrmWyj(wez_wynik());

    if (!StrmWej.is_open())
    {
        cerr << ":( Niepowiodlo sie otwarcie pliku: " << wez_wzor() << endl;
        return false;
    }
    if (!StrmWyj.is_open())
    {
        cerr << ":( Niepowiodlo sie otwarcie pliku: " << wez_wynik() << endl;
        return false;
    }

    return TworzGoreZOstrymSzczytemstrm(StrmWej, StrmWyj);
}

bool Gora_ostry::czy_kolizja(Wektor3D centrum, double promien)
{
    Wektor3D dlugosci_podstawy = wez_skale();
    double odleglosc_x = fabs(centrum[0] - lokalizacja[0]), odleglosc_y = fabs(centrum[1] - lokalizacja[1]);
    double dlg_x = dlugosci_podstawy[0] / 2, dlg_y = dlugosci_podstawy[1] / 2;


    if ((promien + dlg_x) > odleglosc_x && (promien + dlg_y) > odleglosc_y)
    {
        return true;
    }
    return false;
}