#include "../inc/Gora_Dluga_Gran.hh"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <string>
#include <unistd.h>
using namespace std;

/*!
 * \brief Tworzy bryłę reprezentującą górę z długą granią.
 *
 * Tworzy zapis wierzchołków bryły geometrycznej reprezentującej górę z
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
bool Gora_dluga_gran::TworzGoreZDlugaGraniastrm(istream &rStrmWej, ostream &rStrmWyj)
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
        if (Wierz[0] < 0)
          Wierz[0] = fabs(Wierz[0]);
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
 * długą granią.
 *
 * \pre Plik wzorcowy zawiera zapis współrzędnych wierzchołków wzorcowego prostapadłościanu.
 *      Zapis ich jest zgodny z formatem pozwalającym poprawnie zwizualizować prostopadłościan
 *      przez program gnuplot.
 *
 * \param[in] sNazwaPlikuWzorcowego - nazwa pliku, który zawiera współrzędne
 *                                   wzorcowego prostopadłościanu.
 * \param[in] sNazwaPlikuFinalnego - nazwa pliku finalnego, do którego zostaną
 *                                   zapisane współrzędne wierzchołków przetransformowanego
 *                                   i odpowiednio zdeformowanego prostopadłościanu.
 * \retval true - plik z wierzcholkami nowej bryły reprezentującej górę z długą granią
 *                 został zapisany poprawnie.
 * \retval false - operacja nie powiodła się.
 */
bool Gora_dluga_gran::TworzGoreZDlugaGrania()
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

  return TworzGoreZDlugaGraniastrm(StrmWej, StrmWyj);
}

bool Gora_dluga_gran::czy_kolizja(Wektor3D centrum, double promien)
{
  Wektor3D dlugosci_podstawy = wez_skale();
  double odleglosc_x = fabs(centrum[0] - lokalizacja[0]), odleglosc_y = fabs(centrum[1] - lokalizacja[1]);
  double dlg_x = dlugosci_podstawy[0] / 2, dlg_y = dlugosci_podstawy[1] / 2;

    // cout<<"lokalizacja dron" << centrum << endl;
    // cout << "lokalizacja gran" << lokalizacja << endl;
    // cout << "odleglosc x" << odleglosc_x << endl;
    // cout << "dlg_x" << dlg_x << endl;
    // cout << "odleglosc y" << odleglosc_y << endl;
    // cout << "dlg_y" << dlg_y << endl;
    // cout << "promien" << promien << endl;


  if ((promien + dlg_x) > odleglosc_x && (promien + dlg_y) > odleglosc_y)
  {
    return true;
  }
  return false;
}