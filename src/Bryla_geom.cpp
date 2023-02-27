#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <string>
#include "../inc/Bryla_geom.hh"
using namespace std;

#define ILOSC_WIERZ_LINII_TWORZACEJ 4

/*!
 * \brief Transformuje współrzędne pojedynczego punktu.
 * 
 * Transformuje współrzędne pojedynczego punktu poprzez ich przeskalowanie i 
 * przesunięcie o zdany wektor translacji. Współczynniki skalowania jak też
 * współrzędne wektora translacji są przekazywane przez parametry tej funkcji.
 *
 * \param[in] KatObrotu_st - kąt, o jaki ma być dokonany obrót. Wartość kąta wyrażona
 *                           jest w stopniach.
 * \param[in,out] wierz - wspolrzedne punktu, który ma zostać poddana transformacji.
 * \param[in] trans - wektor translacji
 */
void bryla::TransformujWspolrzednePunktu(
    double KatObrotu_st,
    Wektor3D &wierzch,
    Wektor3D trans)
{
  Macierz3x3 rot({{cos(stop_to_rad(KatObrotu_st)), -sin(stop_to_rad(KatObrotu_st)), 0}, {sin(stop_to_rad(KatObrotu_st)), cos(stop_to_rad(KatObrotu_st)), 0}, {0, 0, 1}});
  wierzch = wierzch * skala;
  wierzch = rot * wierzch + trans;
}

/*!
 * \brief  Transformuje całą bryłę.
 *
 *  Czyta ze strumienia wejściowego współrzędne wierzchołków bryły, dokonuje 
 *  ich transformacji (skalowanie, obrót i translacja)
 *  Zapisuje do strumienia współrzędne wierzchołków przetransformowanej bryły
 *  w ten sposób, aby mogły korpus mógł być poprawnie narysowany przez program gnuplot.
 *  \param[in,out] StrmWe_DaneWejsciowe - strumień zawierający opis bryły, która ma podlegać
 *                                        transformacji. Współrzędne z tego strumienia są
 *                                        tylko czytane.
 *  \param[in,out] StrmWy_DaneWynikowe - strumień zawierający opis bryły po dokonanej tranformacji.
 * \param[in] KatObrotu_st - kąt, o jaki ma być dokonany obrót. Wartość kąta wyrażona
 *                           jest w stopniach.
 * \param[in] trans - wektor translacji.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu
 *                 niepowodzenia odczytu lub zapisu do strumienia.
 */
bool bryla::TworzOpisPrzetransformowanejBryly(
    istream &StrmWe_DaneWejsciowe,
    ostream &StrmWy_DaneWynikowe,
    double KatObrotu_st,
    Wektor3D trans)
{
  assert(StrmWe_DaneWejsciowe.good());
  assert(StrmWy_DaneWynikowe.good());

  Wektor3D wierzch;
  StrmWe_DaneWejsciowe >> wierzch;
  while (!StrmWe_DaneWejsciowe.fail())
  {
    for (unsigned int IloscWierzcholkow = 0; IloscWierzcholkow < ILOSC_WIERZ_LINII_TWORZACEJ;
         ++IloscWierzcholkow)
    {
      TransformujWspolrzednePunktu(KatObrotu_st,
                                   wierzch,
                                   trans);
      StrmWy_DaneWynikowe << wierzch;
      StrmWe_DaneWejsciowe >> wierzch;
      assert(IloscWierzcholkow == ILOSC_WIERZ_LINII_TWORZACEJ - 1 || !StrmWe_DaneWejsciowe.fail());
    }

    StrmWy_DaneWynikowe << endl;
  }
  return !StrmWy_DaneWynikowe.fail();
}

/*!
 * \brief  Transformuje całą bryłę.
 *
 *  Czyta z pliku wejściowego współrzędne wierzchołków bryły, dokonuje 
 *  ich transformacji (skalowanie, obrót i translacja)
 *  Zapisuje do drugiego pliku współrzędne wierzchołków przetransformowanej bryły
 *  w ten sposób, aby mogły korpus mógł być poprawnie narysowany przez program gnuplot.
 *  \param[in,out] NazwaPliku_DaneWejsciowe - nazwa pliku zawierający opis bryły, która ma podlegać
 *                                        transformacji. Współrzędne z tego strumienia są
 *                                        tylko czytane.
 *  \param[in,out] NazwaPliku_DaneWynikowe - nazwa pliku, który ma zawierać opis bryły
 *                                         po dokonanej tranformacji.
 * \param[in] KatObrotu_st - kąt, o jaki ma być dokonany obrót. Wartość kąta wyrażona
 *                           jest w stopniach.

 * \param[in] trans - wektor translacji
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku.
 */
bool bryla::TworzOpisPrzetranformowanejBryly(
    const char *NazwaPliku_DaneWejsciowe,
    const char *NazwaPliku_DaneWynikowe,
    double KatObrotu_st,
    Wektor3D trans)
{
  ifstream plik_bryla_wzor(NazwaPliku_DaneWejsciowe);
  ofstream plik_bryla_wynik(NazwaPliku_DaneWynikowe);

  if (!plik_bryla_wzor.is_open())
  {
    cerr << endl
         << " Blad otwarcia do odczytu pliku: " << NazwaPliku_DaneWejsciowe << endl
         << endl;
    return false;
  }

  if (!plik_bryla_wynik.is_open())
  {
    cerr << endl
         << " Blad otwarcia do odczytu pliku: " << NazwaPliku_DaneWynikowe << endl
         << endl;
    return false;
  }

  return TworzOpisPrzetransformowanejBryly(
      plik_bryla_wzor,
      plik_bryla_wynik,
      KatObrotu_st,
      trans);
}

/*!
 * \brief Transformuje współrzędne wierzchołka
 *
 * Transformuje współrzędne wierzchołka mnożąc je przez współczynniki skali dla
 * każdej z osi osobno, a następnie dodając współrzędne punktu wektora
 * translacji.
 *
 * \param[in,out] Wierzch - wartość współrzędnych wierzchołka.
 * \param[in] Trans - wektor translacji.
 */
void bryla::TransformujWierzcholek(Wektor3D &wierzch, Wektor3D trans)
{
  wierzch = skala * wierzch + trans;
}