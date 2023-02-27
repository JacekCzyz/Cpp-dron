#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
using namespace std;
#define H_LOTU 80.0

/*!
 * \brief Przelicza wartość kąta ze stopni na radiany.
 *
 * Przelicza wartość kąta ze stopni na radiany.
 * \param[in] Kat_st - wartość kąta wyrażona w stopniach.
 * \return Wartość przeliczonego kąta wyrażona w radianach.
 */
double stop_to_rad(double Kat_st)
{
  return Kat_st * M_PI / 180;
}

vector<Wektor3D> wczytaj_trase(double &kat, Wektor3D lok_drona, double orient)
{
  vector<Wektor3D> trasa;
  double odleglosc, delta_x, delta_y;
  cout << "Podaj kat" << endl;
  while (1)
  {
    cin >> kat;
    if (cin.fail())
    {
      cout << "wprowadz ponownie" << endl;
      cin.clear();
      cin.ignore(10000, '\n');
    }
    else
    {
      cin.clear();
      cin.ignore(10000, '\n');
      break;
    }
  }
  cout << "podaj odleglosc do przebycia" << endl;
  while (1)
  {
    cin >> odleglosc;
    if (cin.fail())
    {
      cout << "wprowadz ponownie" << endl;
      cin.clear();
      cin.ignore(10000, '\n');
    }
    else
    {
      cin.clear();
      cin.ignore(10000, '\n');
      break;
    }
  }
  double kat_cel = kat + orient;
  delta_y = cos(stop_to_rad(kat_cel)) * odleglosc;
  delta_x = sin(stop_to_rad(kat_cel)) * odleglosc;
  Wektor3D temp = lok_drona;

  if (trasa.size() != 0)
    trasa.clear();

  temp[2] = H_LOTU;
  trasa.push_back(lok_drona);
  trasa.push_back(temp);
  temp[0] = temp[0] + delta_y;
  temp[1] = temp[1] + delta_x;
  trasa.push_back(temp);
  temp[2] = 0;
  trasa.push_back(temp);
  return trasa;
}

void wczytaj_nowa_trase(vector<Wektor3D> &stara_trasa, double kat_cel)
{
  // cout << stara_trasa[3] << stara_trasa[2] << endl;
  double odleglosc = sqrt(pow(stara_trasa[2][0] - stara_trasa[1][0], 2) + pow(stara_trasa[2][1] - stara_trasa[1][1], 2));
  odleglosc = odleglosc + 10;
  // cout<<odleglosc<<endl;
  double delta_x, delta_y;

  // double kat_cel = kat + orient;
  delta_y = cos(stop_to_rad(kat_cel)) * odleglosc;
  delta_x = sin(stop_to_rad(kat_cel)) * odleglosc;
  Wektor3D temp = stara_trasa[0];

  stara_trasa.clear();

  stara_trasa.push_back(temp);
  temp[2] = H_LOTU;
  stara_trasa.push_back(temp);
  temp[0] = temp[0] + delta_y;
  temp[1] = temp[1] + delta_x;
  stara_trasa.push_back(temp);
  temp[2] = 0;
  stara_trasa.push_back(temp);
}