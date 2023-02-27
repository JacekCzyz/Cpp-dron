#ifndef BRYLA_GEOM_HH
#define BRYLA_GEOM_HH

#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "pomocnicze.hh"

#include <iostream>
#include <fstream>
#include <string>

/*!
 * \file
 * \brief Plik zawiera definicje klasy bryla
 */

/*!
 * \brief  klasa definiuje pojecie bryly
 *
 *  klasa posiada pole Wektor3D z jego skala oraz dwie nazwy plikow, jeden to plik
 *  z bryla wzorcowa, drugi z bryla wynikowa
 */

class bryla
{
  const char *plik_bryla_wzor;
  const char *plik_bryla_wynik;
  Wektor3D skala;

public:
  /*!
 * \brief  Konstruktory odpowienio inicjalizujace bryle
 *
 *  bryla zainicjowana pustymi wskaznikami lub jesli podane sa argumenty, odpowiednimi nazwami
 */
  bryla()
  {
    plik_bryla_wynik = nullptr;
    plik_bryla_wzor = nullptr;
    skala = {1, 1, 1};
  }
  bryla(const char *nazwa_wzor, const char *nazwa_wynik, Wektor3D nowa_skala)
  {
    plik_bryla_wynik = nazwa_wynik;
    plik_bryla_wzor = nazwa_wzor;
    skala = nowa_skala;
  }

  /*!
 * \brief  funkcje zwracaja nazwy plikow
 */
  const char *wez_wzor() { return plik_bryla_wzor; }
  const char *wez_wynik() { return plik_bryla_wynik; }
  /*!
 * \brief  funkcja zwracaja wartosc skali
 */
  const Wektor3D wez_skale() { return skala; }
  /*!
 * \brief  funkcja zmieniajaca wartosc skali
 *
 * \param[in] nowa_skala - wektor opisujacy nowa skale
 */
  void przeskaluj(Wektor3D nowa_skala) { skala = nowa_skala; }

  /*!
 * \brief   Zmieniajaca wspolrzedne punktu
 *
 * W wyniku dzialania odpowiednio modyfikowane sa wartosci
 *  \param[in] Kat_Obrotu_st - kat obrotu
 *  \param[in] wierzch - wspolrzedne transformowanego punktu
 *  \param[in] trans - wspolrzedne przesuniecia punktu
 */
  void TransformujWspolrzednePunktu(
      double KatObrotu_st,
      Wektor3D &wierzch,
      Wektor3D trans);

  /*!
 * \brief   Funkcja opisuje bryle
 *
 * W wyniku dzialania odpowiednio modyfikowane sa wartosci sa wpisywane na strumien
 *  \param[in] StrmWe_DaneWejsciowe - strumien danych wejsciowych
 *  \param[in] StrmWy_DaneWynikowe - strumien danych wyjsciowych
 *  \param[in] Kat_Obrotu_st - kat obrotu
 *  \param[in] trans - wspolrzedne przesuniecia punktu
 */
  bool TworzOpisPrzetransformowanejBryly(
      std::istream &StrmWe_DaneWejsciowe,
      std::ostream &StrmWy_DaneWynikowe,
      double KatObrotu_st,
      Wektor3D trans);

  /*!
 * \brief   Funkcja opisuje bryle
 *
 * W wyniku dzialania odpowiednio modyfikowane sa wartosci sa wpisywane do pliku wynikowymi
 *  \param[in] plik_bryla_wzor - plik z danymi wzorcowymi
 *  \param[in] Kat_Obrotu_st - kat obrotu
 *  \param[in] trans - wspolrzedne przesuniecia punktu
 */
  bool TworzOpisPrzetranformowanejBryly(
      const char *plik_bryla_wzor,
      const char *NazwaPliku_DaneWynikowe,
      double KatObrotu_st,
      Wektor3D trans);

  /*!
 * \brief Transformuje współrzędne wierzchołka
 *
 * Transformuje współrzędne wierzchołka mnożąc je przez współczynniki skali dla
 * każdej z osi osobno, a następnie dodając współrzędne punktu wektora
 * translacji.
 *
 * \param[in] trans - współrzędne wektora translacji.
 * \param[in] wierzch - współrzędne wierzcholka.
 */
  void TransformujWierzcholek(Wektor3D &wierzch, Wektor3D trans);

  /*!
    * \brief metdy wirtualne rozwiniete pozniej w odpowiednich klasach
    *
    * Sluza to tworzenia poszczegolnych elementow powierzchni oraz zwracaja odpowiednie, potrzebne wartosci
    */
  virtual std::string ret_ident() { return "false"; }
  virtual Wektor3D ret_lok() { return {0, 0, 0}; }

  virtual bool czy_kolizja(Wektor3D, double) {return false;}
};

#endif