#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <string>
#include <unistd.h>
#include <list>
#include <memory>
#include "../inc/Dron.hh"
using namespace std;

#define SKALA_ROTORA \
  {                  \
    8, 8, 2          \
  }
#define SKALA_KORPUSU \
  {                   \
    10, 8, 4          \
  }
#define SKALA_JEDNOSTKOWA \
  {                       \
    1, 1, 1               \
  }

#define PLIK_WZORCOWEGO_SZESCIANU "bryly_wzorcowe/szescian.dat"
#define PLIK_WZORCOWEGO_GRANIASTOSLUPA6 "bryly_wzorcowe/graniastoslup6.dat"
#define PLIK_KORPUSU_DRONA1 "dat/korpus_drana1.dat"

#define PLIK_ROBOCZY__DRON1_KORPUS "dat/PlikRoboczy_Dron1_Korpus.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR1 "dat/PlikRoboczy_Dron1_Rotor1.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR2 "dat/PlikRoboczy_Dron1_Rotor2.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR3 "dat/PlikRoboczy_Dron1_Rotor3.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR4 "dat/PlikRoboczy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__DRON1_KORPUS "dat/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1 "dat/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2 "dat/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3 "dat/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4 "dat/PlikWlasciwy_Dron1_Rotor4.dat"

#define PLIK_KORPUSU_DRONA2 "dat/korpus_drana2.dat"

#define PLIK_ROBOCZY__DRON2_KORPUS "dat/PlikRoboczy_Dron2_Korpus.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR1 "dat/PlikRoboczy_Dron2_Rotor1.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR2 "dat/PlikRoboczy_Dron2_Rotor2.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR3 "dat/PlikRoboczy_Dron2_Rotor3.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR4 "dat/PlikRoboczy_Dron2_Rotor4.dat"

#define PLIK_WLASCIWY__DRON2_KORPUS "dat/PlikWlasciwy_Dron2_Korpus.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR1 "dat/PlikWlasciwy_Dron2_Rotor1.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR2 "dat/PlikWlasciwy_Dron2_Rotor2.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR3 "dat/PlikWlasciwy_Dron2_Rotor3.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR4 "dat/PlikWlasciwy_Dron2_Rotor4.dat"

/*!
 * \brief Tworzy pliku pozwalające na wizualizację drona.
 * 
 * Zapisuje do odpwiednich plików opisy brył tworzących wizualizację drona.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku.
 */
bool dron::TworzDrona()
{
  static double KatObrotuRotora_st = 0;
#define TRANSLACJA_ROTOR_LEWY_PRZEDNI \
  {                                   \
    5, 4, 5                           \
  }
#define TRANSLACJA_ROTOR_PRAWY_PRZEDNI \
  {                                    \
    5, -4, 5                           \
  }
#define TRANSLACJA_ROTOR_LEWY_TYLNY \
  {                                 \
    -5, 4, 5                        \
  }
#define TRANSLACJA_ROTOR_PRAWY_TYLNY \
  {                                  \
    -5, -4, 5                        \
  }

  //----------------------------------------------------------
  // Korpus drona jest podniesiony o 4. Dzięki temu początek układu
  // współrzędnych drona jest na środku dolnej podstawy korpusu.
  //
  if (identyfikator == 1)
  {
    if (!korpus.TworzKorpus(PLIK_ROBOCZY__DRON1_KORPUS, 0, {0, 0, 2}))
      return false;

    if (!rotor[0].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR1,
                             KatObrotuRotora_st, TRANSLACJA_ROTOR_LEWY_PRZEDNI))
      return false;
    if (!rotor[1].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR2,
                             -KatObrotuRotora_st, TRANSLACJA_ROTOR_PRAWY_PRZEDNI))
      return false;
    if (!rotor[2].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR3,
                             -KatObrotuRotora_st, TRANSLACJA_ROTOR_LEWY_TYLNY))
      return false;
    if (!rotor[3].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR4,
                             KatObrotuRotora_st, TRANSLACJA_ROTOR_PRAWY_TYLNY))
      return false;
  }
  else
  {
    if (!korpus.TworzKorpus(PLIK_ROBOCZY__DRON2_KORPUS, 0, {0, 0, 2}))
      return false;

    if (!rotor[0].TworzRotor(PLIK_ROBOCZY__DRON2_ROTOR1,
                             KatObrotuRotora_st, TRANSLACJA_ROTOR_LEWY_PRZEDNI))
      return false;
    if (!rotor[0].TworzRotor(PLIK_ROBOCZY__DRON2_ROTOR2,
                             -KatObrotuRotora_st, TRANSLACJA_ROTOR_PRAWY_PRZEDNI))
      return false;
    if (!rotor[0].TworzRotor(PLIK_ROBOCZY__DRON2_ROTOR3,
                             -KatObrotuRotora_st, TRANSLACJA_ROTOR_LEWY_TYLNY))
      return false;
    if (!rotor[0].TworzRotor(PLIK_ROBOCZY__DRON2_ROTOR4,
                             KatObrotuRotora_st, TRANSLACJA_ROTOR_PRAWY_TYLNY))
      return false;
  }
#define SKOK_OBROTU_ROTOROW_stopnie 10
  KatObrotuRotora_st += SKOK_OBROTU_ROTOROW_stopnie;
  return true;
}

/*!
 * \brief Ustawia dron w żądanej pozycji i orientacji.
 *
 * Dron zostaje przeniesiony do wskazanej pozycji. Jego orientacja zostaje zmieniona
 * zgodnie z zadanym kątem.
 *
 * \param[in] KatOrDrona_st - kąta orientacji drona. Jest to kąt względem osi OZ.
 *                            Wartość orientacji drona wyrażona jest w stopniach.
 * \param[in] x_PozDrona - x-owa współrzędna pozycji drona.
 * \param[in] y_PozDrona - y-owa współrzędna pozycji drona.
 * \param[in] z_PozDrona - z-owa współrzędna pozycji drona.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - w przypadku przeciwnym.
 *                 Może się to zdarzyć, gdy niepowiedzie się otwarcie jednego z plików,
 *                 z których korzysta ta funkcja,
 *                 lub niepowodzenia odczytu lub zapisu do wspomnianych plików.
 */
bool dron::PrzemiescDrona()
{

  if (!TworzDrona())
    return false;
  //--------------------------------------------------
  // Transformacja elementów drona do właściwej pozycji
  //
  const char *NazwyPlikowRoboczych1[] = {PLIK_ROBOCZY__DRON1_KORPUS, PLIK_ROBOCZY__DRON1_ROTOR1,
                                         PLIK_ROBOCZY__DRON1_ROTOR2, PLIK_ROBOCZY__DRON1_ROTOR3,
                                         PLIK_ROBOCZY__DRON1_ROTOR4, nullptr};

  const char *NazwyPlikowRoboczych2[] = {PLIK_ROBOCZY__DRON2_KORPUS, PLIK_ROBOCZY__DRON2_ROTOR1,
                                         PLIK_ROBOCZY__DRON2_ROTOR2, PLIK_ROBOCZY__DRON2_ROTOR3,
                                         PLIK_ROBOCZY__DRON2_ROTOR4, nullptr};

  if (identyfikator == 1)
  {
    for (unsigned int Idx = 0; NazwyPlikowRoboczych1[Idx] != nullptr; ++Idx)
    {
      if (Idx <= 3)
      {
        rotor[Idx].przeskaluj(SKALA_JEDNOSTKOWA);
        if (!rotor[Idx].TworzOpisPrzetranformowanejBryly(NazwyPlikowRoboczych1[Idx], rotor[Idx].wez_wynik(),
                                                         orient,
                                                         lokacja))
          return false;
      }
      else
      {
        korpus.przeskaluj(SKALA_JEDNOSTKOWA);
        if (!korpus.TworzOpisPrzetranformowanejBryly(NazwyPlikowRoboczych1[Idx], korpus.wez_wynik(),
                                                     orient,
                                                     lokacja))
          return false;
      }
    }
  }
  else
  {
    {
      for (unsigned int Idx = 0; NazwyPlikowRoboczych2[Idx] != nullptr; ++Idx)
      {
        if (Idx <= 3)
        {
          rotor[Idx].przeskaluj(SKALA_JEDNOSTKOWA);
          if (!rotor[Idx].TworzOpisPrzetranformowanejBryly(NazwyPlikowRoboczych2[Idx], rotor[Idx].wez_wynik(),
                                                           orient,
                                                           lokacja))
            return false;
        }
        else
        {
          korpus.przeskaluj(SKALA_JEDNOSTKOWA);
          if (!korpus.TworzOpisPrzetranformowanejBryly(NazwyPlikowRoboczych2[Idx], korpus.wez_wynik(),
                                                       orient,
                                                       lokacja))
            return false;
        }
      }
    }
  }
  return true;
}

#define PLIK_TRASY_PRZELOTU "dat/trasa_przelotu.dat"

/*!
 * \brief Dodaje trasę przelotu.
 *
 * Tworzony jest plik z trasę przelotu w postaci łamanej.
 * Nazwa pliku zostaje dodana do łącza do gnuplota.
 * Dzięki temu dane zawarte w tym pliku zostaną użyte przez
 * gnuplota do narysowania łamanej.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - w przypadku przeciwnym.
 *                 Może się to zdarzyć, gdy niepowiedzie się otwarcie plików,
 *                 do którego zapisywane są współrzędne łamanej modelującej ścieżkę
 *                 przelotu drona, lub niepowodzenia zapisu do tego pliku.
 */
bool dron::DodajTrasePrzelotu(PzG::LaczeDoGNUPlota &Lacze, std::vector<Wektor3D> trasa)
{
  ofstream StrmWy(PLIK_TRASY_PRZELOTU);


  if (!StrmWy.is_open())
  {
    cerr << endl
         << " Nie mozna otworzyc do zapisu pliku: " << PLIK_TRASY_PRZELOTU << endl
         << endl;
    return false;
  }

  StrmWy << trasa[0] << endl
         << trasa[1] << endl
         << trasa[2] << endl
         << trasa[3] << endl;
  Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
  return !StrmWy.fail();
}

/*!
 * \brief Animacja przelotu drona.
 *
 * Animacja przelotu drona.
 * Animacja ta jest robiona na "sztywno"
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - w przypadku przeciwnym.
 *                 Może się to zdarzyć, gdy niepowiedzie się otwarcie jednego z plików,
 *                 z których korzysta ta funkcja,
 *                 lub niepowodzenia odczytu lub zapisu do wspomnianych plików.
 */
bool dron::AnimacjaLotuDrona(PzG::LaczeDoGNUPlota &Lacze, double kat, std::list<std::shared_ptr<bryla>> elementy_powierzchni)
{
  ifstream StrmWe(PLIK_TRASY_PRZELOTU);

  double cel_orient = orient + kat;

  Wektor3D trasa1, trasa2, trasa3, trasa4;

  if (!StrmWe.is_open())
  {
    cerr << endl
         << " Blad otwarcia do odczytu pliku: " << PLIK_TRASY_PRZELOTU << endl
         << endl;
    return false;
  }

  StrmWe >> trasa1 >> trasa2 >> trasa3 >> trasa4;

  //-------------------------------------
  // Wznoszenie ...
  //
  std::cout << endl
            << "Wznoszenie ... " << endl;
  for (; lokacja[2] <= trasa2[2]; lokacja[2] += 1)
  {
    if (!PrzemiescDrona())
      return false;
    usleep(100000); // 0.1 ms
    Lacze.Rysuj();
  }
  lokacja[2] -= 0.5;

  std::cout << "Zmiana orientacji ... " << endl;
  if (kat > 0)
  {
    for (; orient <= cel_orient; orient += 5)
    {
      if (!PrzemiescDrona())
        return false;
      usleep(100000);
      Lacze.Rysuj();
    }
    orient -= 5;
  }
  else
  {
    for (; orient >= cel_orient; orient -= 5)
    {
      if (!PrzemiescDrona())
        return false;
      usleep(100000);
      Lacze.Rysuj();
    }
    orient += 5;
  }
  n_orient(cel_orient);
  //-------------------------------------
  // Lot do przodu ...
  //
  std::cout << "Lot do przodu ... " << endl;
  while (1)
  {
    double deltax = trasa3[0] - trasa2[0];
    double deltay = trasa3[1] - trasa2[1];

    double wzrost_y = deltay / deltax;
    if (deltax > 0)
    {
      if (deltay > 0)
      {
        for (; lokacja[0] <= trasa3[0]; lokacja[0] += 1, lokacja[1] += wzrost_y)
        {
          if (!PrzemiescDrona())
            return false;
          usleep(100000);
          Lacze.Rysuj();
        }
        lokacja[0] -= 1, lokacja[1] -= wzrost_y;
      }
      else
      {
        for (; lokacja[0] <= trasa3[0]; lokacja[0] += 1, lokacja[1] += wzrost_y)
        {
          if (!PrzemiescDrona())
            return false;
          usleep(100000);
          Lacze.Rysuj();
        }
        lokacja[0] -= 1, lokacja[1] += wzrost_y;
      }
    }

    if (deltax < 0)
    {
      if (deltay > 0)
      {
        for (; lokacja[0] >= trasa3[0]; lokacja[0] -= 1, lokacja[1] -= wzrost_y)
        {
          if (!PrzemiescDrona())
            return false;
          usleep(100000);
          Lacze.Rysuj();
        }
        lokacja[0] += 1, lokacja[1] += wzrost_y;
      }
      else
      {
        for (; lokacja[0] >= trasa3[0]; lokacja[0] -= 1, lokacja[1] -= wzrost_y)
        {
          if (!PrzemiescDrona())
            return false;
          usleep(100000);
          Lacze.Rysuj();
        }
        lokacja[0] += 1, lokacja[1] -= wzrost_y;
      }
    }
    n_lok(trasa3);

    if (Czy_mozna_ladawac(elementy_powierzchni) == true)
    {
      cout << "mozna ladawac" << endl;
      break;
    }
    else
      cout << "nie mozna ladawac" << endl;

    vector<Wektor3D> trasa;
    trasa.push_back(trasa1);
    trasa.push_back(trasa2);
    trasa.push_back(trasa3);
    trasa.push_back(trasa4);
    wczytaj_nowa_trase(trasa, cel_orient);

    // cout << trasa[1] << trasa[2] << trasa[3] << trasa[4] << endl;

    if (!DodajTrasePrzelotu(Lacze, trasa))
      return 1;
    Lacze.Rysuj();
    trasa3 = trasa[2];
    trasa4 = trasa[3];

    cout << "poprawa lokacji" << endl;
  }

  //-------------------------------------
  // Opadanie ...
  //
  std::cout << "Opadanie ... " << endl;
  for (; lokacja[2] >= trasa4[2]; lokacja[2] -= 2)
  {
    if (!PrzemiescDrona())
      return false;
    usleep(100000); // 0.1 ms
    Lacze.Rysuj();
  }
  n_lok(trasa4);
  return true;
}

void dron::n_lok(Wektor3D n_lok)
{
  Wektor3D temp1(TRANSLACJA_ROTOR_LEWY_PRZEDNI), temp2(TRANSLACJA_ROTOR_LEWY_TYLNY), temp3(TRANSLACJA_ROTOR_PRAWY_PRZEDNI), temp4(TRANSLACJA_ROTOR_PRAWY_TYLNY);
  cout << n_lok << endl;
  lokacja = n_lok;
  korpus.n_lok(n_lok);
  rotor[0].n_lok((n_lok + temp1));
  rotor[1].n_lok(n_lok + temp2);
  rotor[2].n_lok(n_lok + temp3);
  rotor[3].n_lok(n_lok + temp4);
  spt_korpus.get()->n_lok(korpus.ret_lok());
  spt_korpus.get()->przeskaluj(SKALA_KORPUSU);
  for (int i = 0; i < 4; i++)
  {
    spt_rotor[i].get()->n_lok(rotor[i].ret_lok());
    spt_rotor[i].get()->przeskaluj(SKALA_ROTORA);
  }
}




bool dron::Czy_mozna_ladawac(std::list<std::shared_ptr<bryla>> elementy_powierzchni)
{
  Wektor3D skala_korp(SKALA_KORPUSU), skala_rot(SKALA_ROTORA);
  Wektor3D lok_centrum({lokacja[0], lokacja[1], 0});
  double promien = 0.5 * (sqrt(pow(skala_korp[0], 2) + (skala_korp[1], 2))) + 0.5 * skala_rot[0];

  for (const shared_ptr<bryla> &elem : elementy_powierzchni)
  {
    if (spt_korpus == elem)
    {
    }
    else if (spt_rotor[0] == elem)
    {
    }
    else if (spt_rotor[1] == elem)
    {
    }
    else if (spt_rotor[2] == elem)
    {
    }
    else if (spt_rotor[3] == elem)
    {
    }
    else
    {
      if (elem->czy_kolizja(lok_centrum, promien) == true)
        return false;
    }
  }
  return true;
}
