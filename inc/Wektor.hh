#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include <iomanip>
#include <cassert>
#include <initializer_list>

/*!
 * \file
 * \brief Plik zawiera definicję szablonu Wektor<>
 */

/*!
 * \brief  Szablon definiuje ogolne pojecie Wektora
 *
 *  Wektor zdefiniowany jako tablica liczb double.
 */
template <int Wymiar>
class Wektor
{
  double wspol[Wymiar];

public:
/*!
 * \brief  Konstruktory odpowienio inicjalizujace wektor
 *
 *  wektor zainicjowany zerami lub jesli podane sa argumenty, odpowiednimi wartosciami
 */
  Wektor();
  Wektor(const std::initializer_list<double> &lista);
  /*!
 * \brief  Przeciazenie operatora mnozenia przez liczbe
 *
 * W wyniku dzialania zwracany jest wektor
 *  \param[in] mnoz - liczba przez jaka mnozony jest wektor
 */
  Wektor operator*(double mnoz);

  Wektor operator*(Wektor mnoz);
  /*!
 * \brief  Przeciazenie operatora dodawania wektora
 *
 * W wyniku dzialania zwracany jest wektor
 *  \param[in] skl - wektor dodawany do wektora
 */
  Wektor operator+(Wektor skl);
  /*!
 * \brief  Przeciazenia operatorow indeksujacych
 *
 *  Przeciazenia pozwalaja odwolywac sie do poszczegolnych pol w wektorze
 */
  double operator[](int ind) const { return wspol[ind]; }
  double &operator[](int ind) { return wspol[ind]; }
};

template <int Wymiar>
Wektor<Wymiar>::Wektor()
{
  for (double &nwspol : wspol)
    nwspol = 0;
}

template <int Wymiar>
Wektor<Wymiar>::Wektor(const std::initializer_list<double> &lista)
{
  assert(lista.size() == Wymiar);
  int ind = 0;
  for (double nwspol : lista)
  {
    wspol[ind] = nwspol;
    ind++;
  }
}

template <int Wymiar>
Wektor<Wymiar> Wektor<Wymiar>::operator*(double mnoz)
{
  Wektor<Wymiar> wynik;
  for (int i = 0; i < Wymiar; i++)
    wynik[i] = wspol[i] * mnoz;
  return wynik;
}

template <int Wymiar>
Wektor<Wymiar> Wektor<Wymiar>::operator*(Wektor mnoz)
{
  Wektor<Wymiar> wynik;
  for (int i = 0; i < Wymiar; i++)
    wynik[i] = wspol[i] * mnoz[i];
  return wynik;
}

template <int Wymiar>
Wektor<Wymiar> Wektor<Wymiar>::operator+(Wektor skl)
{
  Wektor<Wymiar> wynik;
  for (int i = 0; i < Wymiar; i++)
    wynik[i] = wspol[i] + skl[i];
  return wynik;
}


/*!
 * \brief  Przeciazenie operatora przesuniecia bitowego w prawo
 */
template <int Wymiar>
inline std::istream &operator>>(std::istream &wej, Wektor<Wymiar> &Wek)
{
  for (int i = 0; i < Wymiar; i++)
    wej >> Wek[i];
  if (wej.fail())
  {
    return wej;
  }
  return wej;
}


/*!
 * \brief  Przeciazenie operatora przesuniecia bitowego w lewo
 */
template <int Wymiar>
inline std::ostream &operator<<(std::ostream &wyj, const Wektor<Wymiar> &Wek)
{
  for (int i = 0; i < Wymiar; i++)
  {
    wyj << std::setw(16) << std::fixed << std::setprecision(10) << Wek[i];
    if (i == (Wymiar - 1))
      wyj << std::endl;
  }
  return wyj;
}

#endif
