#ifndef POMOCNICZE_HH
#define POMOCNICZE_HH


#include <iostream>
#include <fstream>
#include <vector>


double stop_to_rad(double Kat_st);

std::vector<Wektor3D>  wczytaj_trase(double &kat, Wektor3D lok_drona, double orient);

void  wczytaj_nowa_trase(std::vector<Wektor3D> &stara_trasa, double orient);


#endif