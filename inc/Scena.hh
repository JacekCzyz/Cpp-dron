#ifndef SCENA_HH
#define SCENA_HH
#include <memory>
#include "Dron.hh"
#include "Plaskowyz.hh"
#include "Gora_Ostry_Szczyt.hh"
#include "Gora_Dluga_Gran.hh"

/*!
 * \file
 * \brief Plik zawiera definicje klasy scena
 */

/*!
 * \brief  klasa definiuje pojecie sceny
 *
 *  scena posiada pole zawierajace tablice dwoch dronow oraz liste elementow powierzchni tytana
 */

class scena
{
    std::list<dron> drony;
    std::list<std::shared_ptr<bryla>> przeszkody;
    // std::list<std::shared_ptr<bryla>> elem_sceny;

public:
    /*!
 * \brief  Konstruktory odpowienio inicjalizujace scene
 *
 *  scena zainicjowana zerami lub jesli podane sa argumenty, odpowiednimi wartosciami
 */
    scena()
    {
        dron temp;
        drony.push_back(temp);
        drony.push_back(temp);
    }
    scena(dron urzadzenie1, dron urzadzenie2)
    {
        drony.push_back(urzadzenie1);
        drony.push_back(urzadzenie2);
        for (int i = 0; i < 4; i++)
        {
            przeszkody.push_back(drony.back().ret_wsk_rotor(i));
        }
        przeszkody.push_back(drony.back().ret_wsk_korpus());
        for (int j = 0; j < 4; j++)
        {
            przeszkody.push_back(drony.front().ret_wsk_rotor(j));
        }
        przeszkody.push_back(drony.front().ret_wsk_korpus());
    }

    /*!
 * \brief  Funkcja zwracajaca wybranego drona
 *
 * funckcja zwraca drona w zaleznosci od wyboru uzytkownika, staje sie on dronem aktywnym
 *  \param[in] wybor - liczba okreslajaca wybor drona przez uzytkownika
 */
    dron &wez_drona(int wybor);

    /*!
 * \brief  Funkcja zwracajaca liste
 *
 * funckcja zwraca referencje do listy dajac mozliwosc uzytkowania i dokonywania zmian w niej
 */
    std::list<std::shared_ptr<bryla>> &wez_liste();
};

#endif