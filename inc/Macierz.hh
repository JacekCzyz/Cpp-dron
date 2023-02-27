#ifndef MACIERZ_HH
#define MACIERZ_HH

#include <iostream>
#include <cassert>
#include <initializer_list>
#include "Wektor3D.hh"

/*!
 * \file
 * \brief Plik zawiera definicję szablonu Macierz<>
 */

/*!
 * \brief  Szablon definiuje ogolne pojecie macierzy
 *
 *  Macierz zdefiniowana jako tablica wektorow.
 */
template <int Wymiar>
class Macierz
{
  Wektor<Wymiar> rzad[Wymiar];

public:
/*!
 * \brief  Konstruktory odpowienio inicjalizujace macierz
 *
 *  Macierz zainicjowana wektorami zerowymi lub jesli podane sa argumenty, odpowiednimi wartosciami
 */
  Macierz(const std::initializer_list<Wektor<Wymiar>> &lista);
  Macierz();
/*!
 * \brief  Przeciazenia operatorow indeksujacych
 *
 *  Przeciazenia pozwalaja odwolywac sie do poszczegolnych pol w macierzy
 */
  Wektor<Wymiar> &operator[](int ind) { return rzad[ind]; }
  Wektor<Wymiar> operator[](int ind) const { return rzad[ind]; }
/*!
 * \brief  Przeciazenie operatora mnozenia przez wektor
 *
 * W wyniku dzialania zwracany jest wektor
 *  \param[in] mnoz - wektor przez jaki mnozona jest macierz
 */
  Wektor<Wymiar> operator*(Wektor<Wymiar> mnoz);
/*!
 * \brief  Przeciazenie operatora mnozenia przez macierz
 *
 * W wyniku dzialania zwracana jest odpowiednia macierz
 *  \param[in] mnoz - macierz przez jaka mnozona jest macierz
 */
  Macierz<Wymiar> operator*(Macierz<Wymiar> mnoz);
};

template <int Wymiar>
Macierz<Wymiar>::Macierz()
{
  for (Wektor<Wymiar> &nrzad : rzad)
  {
    for(int i=0;i<Wymiar;i++)
    nrzad[i]=0;
  }
}

template <int Wymiar>
Wektor<Wymiar> Macierz<Wymiar>::operator*(Wektor<Wymiar> mnoz)
{
  Wektor<Wymiar> Wynik;
  for (int i = 0; i < Wymiar; i++)
  {
    double temp1 = 0, temp2 = 0;
    for (int j = 0; j < Wymiar; j++)
    {
      temp1 = rzad[i][j] * mnoz[j];
      temp2 += temp1;
    }
    Wynik[i] = temp2;
  }
  return Wynik;
}

template <int Wymiar>
Macierz<Wymiar> Macierz<Wymiar>::operator*(Macierz<Wymiar> mnoz)
{
  Macierz<Wymiar> Wynik;
  for (int i = 0; i < Wymiar; i++)
  {
    int indx1 = 0, indx2=0;
    double suma = 0;
    for (int j = 0; j < Wymiar; j++)
    {
      suma = suma + (this->rzad[i][j] * mnoz[indx1][indx2]);
      indx1++;
      if (j == (Wymiar - 1))
      {
        Wynik[i][indx2] = suma;
        suma=0;
        if(indx2<Wymiar){
        j=-1;
        indx2++;
        indx1=0;}
        else
        break;
      }
    }
  }
  return Wynik;
}

template <int Wymiar>
Macierz<Wymiar>::Macierz(const std::initializer_list<Wektor<Wymiar>> &lista)
{
  assert(lista.size() == Wymiar);
  int ind = 0;
  for (Wektor<Wymiar> nwek : lista)
  {
    rzad[ind] = nwek;
    ind++;
  }
}

/*!
 * \brief  Przeciazenie operatora przesuniecia bitowego w lewo
 */
template <int Wymiar>
inline std::ostream &operator<<(std::ostream &wyj, const Macierz<Wymiar> &Mac)
{
  for (int i = 0; i < Wymiar; i++)
  {
    wyj << Mac[i];
  }
  return wyj;
}

#endif
