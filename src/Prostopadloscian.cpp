#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <string>
#include <unistd.h>
#include "../inc/Prostopadloscian.hh"

using namespace std;

#define PLIK_WZORCOWEGO_SZESCIANU "bryly_wzorcowe/szescian.dat"

#define SKALA_ROTORA \
    {                \
        8, 8, 2      \
    }
#define SKALA_KORPUSU \
    {                 \
        10, 8, 4      \
    }
#define SKALA_JEDNOSTKOWA \
    {                     \
        1, 1, 1           \
    }



/*!
 * \brief Tworzy plik z wierzchołkami były modelującej korpus drona.
 *
 * Tworzy plik, w którym zostają zapise współrzędne wierzchołków
 * tworzących korpus drona. Zapisane one są w ten sposób, aby program gnuplot
 * mógł wyświetlić prostopadłościan. Tworzona bryła zostaje obrócona
 * względem swojej pierwotnej orientacji o zadany kąt oraz przesunięta o wektor
 * translacji, którego współrzędne podane są jako parametry tej funkcji.
 *
 * \param[in] NazwPliku_KorpusuWDronie - nazwa pliku, w którym zostaną zapisane współrzędne
 *                                       wierzchołków bryły tworzącej korpus drona.
 * \param[in] KatObrotuKorpusu_st - kąt obrotu korpusu. Jego wartość wyrażona jest w stopniach.
 * \param[in] tx_trans - x-owa współrzędna wektora translacji.
 * \param[in] ty_trans - y-owa współrzędna wektora translacji.
 * \param[in] tz_trans - z-owa współrzędna wektora translacji.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku. 
 */
bool prostopadloscian::TworzKorpus(const char *Plik_Korpus,
                       double KatObrotuKorpusu_st,
                       Wektor3D trans)
{
  przeskaluj(SKALA_KORPUSU);
  return TworzOpisPrzetranformowanejBryly(wez_wzor(), Plik_Korpus, KatObrotuKorpusu_st, trans);
}


bool prostopadloscian::czy_kolizja(Wektor3D centrum, double promien)
{
  Wektor3D dlugosci_podstawy = wez_skale();
  double odleglosc_x= fabs(centrum[0]-lokalizacja[0]), odleglosc_y=fabs(centrum[1]-lokalizacja[1]);
  double dlg_x=dlugosci_podstawy[0]/2, dlg_y=dlugosci_podstawy[1]/2;

  if ((promien + dlg_x) > odleglosc_x && (promien + dlg_y) > odleglosc_y)
  {
    return true;}
  return false;
}