#ifndef DRON_HH
#define DRON_HH
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

#define PLIK_WLASCIWY__DRON1_KORPUS "dat/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1 "dat/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2 "dat/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3 "dat/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4 "dat/PlikWlasciwy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__DRON2_KORPUS "dat/PlikWlasciwy_Dron2_Korpus.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR1 "dat/PlikWlasciwy_Dron2_Rotor1.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR2 "dat/PlikWlasciwy_Dron2_Rotor2.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR3 "dat/PlikWlasciwy_Dron2_Rotor3.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR4 "dat/PlikWlasciwy_Dron2_Rotor4.dat"

#include "Prostopadloscian.hh"
#include "Graniastoslup.hh"
#include "lacze_do_gnuplota.hh"
#include <list>
#include <memory>

/*!
 * \file
 * \brief Plik zawiera definicje klasy dron
 */

/*!
 * \brief  klasa definiuje pojecie drona
 *
 *  Dron posiada pole Wektor3D z jego lokacja, double z orientacja(kat w stopniach)
 *  tablice zawierajaca 4 graniastoslupy(rotory), pole prostopadloscian(korpus) oraz identyfikator drona
 */
class dron
{
  Wektor3D lokacja;
  double orient;
  graniastoslup rotor[4];
  std::shared_ptr<graniastoslup> spt_rotor[4] = {std::make_shared<graniastoslup>(rotor[0]), std::make_shared<graniastoslup>(rotor[1]), std::make_shared<graniastoslup>(rotor[2]), std::make_shared<graniastoslup>(rotor[3])};
  prostopadloscian korpus;
  std::shared_ptr<prostopadloscian> spt_korpus = std::make_shared<prostopadloscian>(korpus);
  int identyfikator;

public:
  /*!
 * \brief  Konstruktory odpowienio inicjalizujace drona
 *
 *  dron zainicjowany zerami lub jesli podane sa argumenty, odpowiednimi wartosciami
 */
  dron()
  {
    graniastoslup tempg;
    prostopadloscian tempp;

    tempg.przeskaluj(SKALA_JEDNOSTKOWA);
    tempp.przeskaluj(SKALA_JEDNOSTKOWA);
    lokacja = {0, 0, 0};
    orient = 0;
    rotor[0] = rotor[1] = rotor[2] = rotor[3] = tempg;
    korpus = tempp;
    identyfikator = 0;
  }
  dron(int n, double kat, Wektor3D lok)
  {

    lokacja = lok;
    orient = kat;
    identyfikator = n;
    if (identyfikator == 1)
    {
      graniastoslup tempg1(PLIK_WLASCIWY__DRON1_ROTOR1, SKALA_ROTORA, kat, lok), tempg2(PLIK_WLASCIWY__DRON1_ROTOR2, SKALA_ROTORA, kat, lok), tempg3(PLIK_WLASCIWY__DRON1_ROTOR3, SKALA_ROTORA, kat, lok), tempg4(PLIK_WLASCIWY__DRON1_ROTOR4, SKALA_ROTORA, kat, lok);
      prostopadloscian tempp(PLIK_WLASCIWY__DRON1_KORPUS, SKALA_KORPUSU, kat, lok);
      rotor[0] = tempg1;
      rotor[1] = tempg2;
      rotor[2] = tempg3;
      rotor[3] = tempg4;
      korpus = tempp;
    }
    else if (identyfikator == 2)
    {
      Wektor3D skala_rot(SKALA_ROTORA), skala_korp(SKALA_KORPUSU);
      Wektor3D temp1(TRANSLACJA_ROTOR_LEWY_PRZEDNI), temp2(TRANSLACJA_ROTOR_LEWY_TYLNY), temp3(TRANSLACJA_ROTOR_PRAWY_PRZEDNI), temp4(TRANSLACJA_ROTOR_PRAWY_TYLNY);
      graniastoslup tempg1(PLIK_WLASCIWY__DRON2_ROTOR1, SKALA_ROTORA, kat, lok), tempg2(PLIK_WLASCIWY__DRON2_ROTOR2, SKALA_ROTORA, kat, lok), tempg3(PLIK_WLASCIWY__DRON2_ROTOR3, SKALA_ROTORA, kat, lok), tempg4(PLIK_WLASCIWY__DRON2_ROTOR4, SKALA_ROTORA, kat, lok);
      prostopadloscian tempp(PLIK_WLASCIWY__DRON2_KORPUS, SKALA_KORPUSU, kat, lok);
      spt_korpus.get()->n_lok(lokacja);
      spt_korpus.get()->przeskaluj({10,8,4});
      for (int i = 0; i < 4; i++)
      {
        spt_rotor[i].get()->n_lok(lokacja);
        spt_rotor[i].get()->przeskaluj({8,8,2});
      }

      rotor[0] = tempg1;
      rotor[1] = tempg2;
      rotor[2] = tempg3;
      rotor[3] = tempg4;
      korpus = tempp;
    }
  }

  /*!
 * \brief  Funkcja zwraca wektor okreslajacy lokacje drona 
 */
  Wektor3D ret_lok() { return lokacja; }

  void n_lok(Wektor3D n_lok);


  /*!
 * \brief  Funkcja zwraca double okreslajacy orientacje drona 
 */
  double ret_orient() { return orient; }

  void n_orient(double kat) { orient = kat; }
  graniastoslup ret_rotor(int num_rot) { return rotor[num_rot]; }
  std::shared_ptr<graniastoslup> ret_wsk_rotor(int num_rot) { return spt_rotor[num_rot]; }
  prostopadloscian ret_korpus() { return korpus; }
  std::shared_ptr<prostopadloscian> ret_wsk_korpus() { return spt_korpus; }

  /*!
 * \brief  Funkcja tworzaca drona
 *
 * W wyniku dzialania zwracana jest prawda/falsz, wewnatrz funkcji wykorzystywane tworzenie korpusu i drona
 */
  bool TworzDrona();

  /*!
 * \brief  Funkcja przesuwajaca drona
 *
 * W wyniku dzialania zwracana jest prawda/falsz, funkcja odpowiednio modyfikuje wspolrzedne drona
 */
  bool PrzemiescDrona();
  /*!
 * \brief  Funkcja dodaje trase przelotu
 *
 * W wyniku dzialania zwracana jest prawda/falsz, odpowiednie wartosci wpisywane do pliku zawierajacego wspolrzedne trasy przelotu
 *  \param[in] Lacze - lacze do programu gnuplot
 *  \param[in] trasa - vector zawierajacy trase przelotu
 */
  bool DodajTrasePrzelotu(PzG::LaczeDoGNUPlota &Lacze, std::vector<Wektor3D> trasa);
  /*!
 * \brief  Funkcja animujaca lot drona

 * W wyniku dzialania zwracana jest prawda/falsz, odpowiednie wartosci wpisywane do pliku zawierajacego wspolrzedne trasy przelotu
 *  \param[in] Lacze - lacze do programu gnuplot
 *  \param[in] kat - zadany kat o jaki powinien sie obrocic dron
 *  \param[in] licz_wek - licznik zliczajacy ilosc ogolem wytworzonych obiektow wektor3D
 *  \param[in] elementy_powierzchni - lista elementow na powierzchni sceny
 */
  bool AnimacjaLotuDrona(PzG::LaczeDoGNUPlota &Lacze, double kat, std::list<std::shared_ptr<bryla>> elementy_powierzchni);

  bool Czy_mozna_ladawac(std::list<std::shared_ptr<bryla>>);
};

#endif