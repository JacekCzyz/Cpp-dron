#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include <vector>
#include <string>
#include <string.h>
#include "lacze_do_gnuplota.hh"
#include "../inc/Scena.hh"

using namespace std;

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

#define PLIK_WLASCIWY__GORA1 "dat/gora1.dat"
#define PLIK_WLASCIWY__GORA2 "dat/gora2.dat"
#define PLIK_WLASCIWY__GORA3 "dat/gora3.dat"
#define PLIK_WLASCIWY__PLASKOWYZ1 "dat/plaskowyz1.dat"

#define PLIK_TRASY_PRZELOTU "dat/trasa_przelotu.dat"

int main()
{
  std::vector<Wektor3D> trasa;

  scena drony({1, 0, {20, 20, 0}}, {2, 0, {50, 80, 0}});

  Wektor3D skala({10, 10, 60}), pozycja({150, 20, 0});
  drony.wez_liste().push_back(make_shared<Gora_dluga_gran>(PLIK_WLASCIWY__GORA1, skala, pozycja));


  skala = {20, 80, 60};
  pozycja = {100, 100, 0};
  drony.wez_liste().push_back(make_shared<Gora_ostry>(PLIK_WLASCIWY__GORA2, skala, pozycja));

  skala = {20, 45, 75};
  pozycja = {90, 120, 0};
  drony.wez_liste().push_back(make_shared<Gora_ostry>(PLIK_WLASCIWY__GORA3, skala, pozycja));

  skala = {50, 60, 15};
  pozycja = {150, 115, 0};
  drony.wez_liste().push_back(make_shared<Plaskowyz>(PLIK_WLASCIWY__PLASKOWYZ1, skala, pozycja));

  PzG::LaczeDoGNUPlota Lacze;
  double kat;
  int wybor_dron = 1;
  Lacze.DodajNazwePliku("bryly_wzorcowe/plaszczyzna.dat");
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_KORPUS);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR4);

  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_KORPUS);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR4);

  Lacze.DodajNazwePliku(PLIK_WLASCIWY__GORA1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__GORA2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__GORA3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__PLASKOWYZ1);

  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.

  Lacze.UstawZakresX(0, 200);
  Lacze.UstawZakresY(0, 200);
  Lacze.UstawZakresZ(0, 120);

  Lacze.UstawRotacjeXZ(64, 65); // Tutaj ustawiany jest widok


  if (!drony.wez_drona(1).PrzemiescDrona())
    return 0;

  if (!drony.wez_drona(2).PrzemiescDrona())
    return 0;

  Lacze.Rysuj(); // Teraz powinno pojawic sie okienko gnuplota
                 // z rysunkiem, o ile istnieje plik "prostopadloscian1.pow"

  cout << "podaj identyfikator drona do uzycia\nDron 1: " << drony.wez_drona(1).ret_lok() << endl;
  cout << "Dron 2: " << drony.wez_drona(2).ret_lok() << endl;
  cout << "Wybierz drona" << endl;
  while (1)
  {
    cin >> wybor_dron;
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
  int licznik_elem_pow = 0;
  char wybor_switch;
  while (wybor_switch != 'k')
  {
    cout << "polozenie aktywnego drona:";
    if (wybor_dron == 1)
      cout << drony.wez_drona(1).ret_lok() << endl;
    else
      cout << drony.wez_drona(2).ret_lok() << endl;

    cout << "Witaj w menu, wybierz jedna z dostepnych opcji:\n d - dodaj element powierzchni\n u - usun element powierzchni\n a - wybierz drona\n p - zadaj parametry przelotu dla aktywnego drona\n m - wyswietl menu \n k-zakoncz prace programu" << endl;
    cin >> wybor_switch;

    switch (wybor_switch)
    {

    case 'u':
    {
      cout << "lista elementow do wyboru:" << endl;
      int licznik = 1;
      const char *nazwa;
      for (const shared_ptr<bryla> &elem : drony.wez_liste())
      {
        
        cout << licznik;
        if ((elem.get()->ret_ident().compare("g")) == 0)
        {
          cout << " dluga gran, lokacja:" << elem.get()->ret_lok() << endl;
        }
        else if ((elem.get()->ret_ident().compare("s")) == 0)
        {
          cout << " ostry szczyt, lokacja:" << elem.get()->ret_lok() << endl;
        }
        else if ((elem.get()->ret_ident().compare("p")) == 0)
        {
          cout << " plaskowyz, lokacja:" << elem.get()->ret_lok() << endl;
        }
        licznik++;
      }

      cout << "wprowadz numer elementu:" << endl;
      while (1)
      {
        cin >> licznik;
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
      auto iter = drony.wez_liste().begin();
      std::advance(iter, licznik - 1);

      nazwa = iter->get()->wez_wynik();
      drony.wez_liste().erase(iter);
      Lacze.UsunNazwePliku(nazwa);
      Lacze.Rysuj();
      break;
    }

    case 'd':
    {
      char wybor_gora;
      Wektor3D skala, lokalizacja;
      cout << "ktory z elementow powierzchni chcesz dodac? Dostepne to:\n p - plaskowyz\n o - gora z ostrym szczytem\n g - gora z dluga grania\n"
           << endl;
      while (1)
      {
        cin >> wybor_gora;
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

      cout << "wprowadz lokalizacje elementu" << endl;
      cin >> lokalizacja;
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "wprowadz skale elementu" << endl;
      cin >> skala;
      cin.clear();
      cin.ignore(10000, '\n');

      std::string nazwa = "dat/" + std::to_string(licznik_elem_pow) + "element.dat";

      char nazwa_char[17];

      strcpy(nazwa_char, nazwa.c_str());

      if (wybor_gora == 'p'){
        drony.wez_liste().push_back(make_shared<Plaskowyz>(nazwa_char, skala, lokalizacja));}
      else if (wybor_gora == 'o'){
        drony.wez_liste().push_back(make_shared<Gora_ostry>(nazwa_char, skala, lokalizacja));}

      else if (wybor_gora == 'g'){
        drony.wez_liste().push_back(make_shared<Gora_dluga_gran>(nazwa_char, skala, lokalizacja));}


      Lacze.DodajNazwePliku(nazwa_char);
      Lacze.Rysuj();
      licznik_elem_pow++;
      break;
    }

    case 'a':
    {
      cout << "dostepne drony:" << endl;
      if (wybor_dron == 1)
      {
        cout << "1 - dron 1(aktywny)" << drony.wez_drona(1).ret_lok() << endl
             << "2 - dron 2" << drony.wez_drona(2).ret_lok() << endl;
      }
      else
      {
        cout << "1 - dron 1" << drony.wez_drona(1).ret_lok() << endl
             << "2 - dron 2(aktywny)" << drony.wez_drona(2).ret_lok() << endl;
      }
      cout << "wprowadz numer drona:" << endl;
      while (1)
      {
        cin >> wybor_dron;
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

      break;
    }

    case 'p':
    {
      if (wybor_dron == 1)
      {
        trasa = wczytaj_trase(kat, drony.wez_drona(1).ret_lok(), drony.wez_drona(1).ret_orient());

        cout << "Nacisnij ENTER, aby pokazac sciezke przelotu drona " << flush;
        cin.ignore(10000, '\n');

        if (!drony.wez_drona(1).DodajTrasePrzelotu(Lacze, trasa))
          return 1;
        Lacze.Rysuj();

        cout << "Nacisnij ENTER, aby wykonac animacje lotu drona " << flush;
        cin.ignore(10000, '\n');
        if (!drony.wez_drona(1).AnimacjaLotuDrona(Lacze, kat, drony.wez_liste()))
          return 1;
      }

      else if (wybor_dron == 2)
      {
        trasa = wczytaj_trase(kat, drony.wez_drona(2).ret_lok(), drony.wez_drona(2).ret_orient());

        cout << "Nacisnij ENTER, aby pokazac sciezke przelotu drona " << flush;
        cin.ignore(10000, '\n');

        if (!drony.wez_drona(2).DodajTrasePrzelotu(Lacze, trasa))
          return 1;
        Lacze.Rysuj();

        cout << "Nacisnij ENTER, aby wykonac animacje lotu drona " << flush;
        cin.ignore(10000, '\n');
        if (!drony.wez_drona(2).AnimacjaLotuDrona(Lacze, kat, drony.wez_liste()))
          return 1;
      }

      Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
      Lacze.Rysuj();

      break;
    }

    case 'm':
      break;

    case 'k':
      break;

    default:
    {
      cout << "niepoprawny wybor" << endl;
      break;
    }
    }
  }
}
