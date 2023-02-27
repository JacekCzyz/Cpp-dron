TASKNO=5
APP=sterowanie-dronem
TASKDIR=${HOME}/edu/po/zad/z${TASKNO}

__start__: obj dat ./${APP}
	rm -f core.* core; ./${APP}

# Tworzy katalog "obj" gdy go nie ma
# 
obj:
	mkdir obj

dat:
	mkdir dat


./${APP}: obj/main.o obj/lacze_do_gnuplota.o obj/Bryla_geom.o obj/Dron.o obj/Graniastoslup.o obj/Plaskowyz.o obj/Gora_Dluga_Gran.o obj/Gora_Ostry_Szczyt.o obj/Macierz3x3.o obj/pomocnicze.o obj/Prostopadloscian.o obj/Scena.o obj/Wektor3D.o obj/Macierz3x3.o
	g++ -Wall -pedantic -std=c++0x -o ./${APP} obj/main.o obj/lacze_do_gnuplota.o obj/Bryla_geom.o obj/Dron.o obj/Graniastoslup.o obj/Plaskowyz.o obj/Gora_Dluga_Gran.o obj/Gora_Ostry_Szczyt.o obj/Macierz3x3.o obj/pomocnicze.o obj/Prostopadloscian.o obj/Scena.o obj/Wektor3D.o obj/Macierz3x3.o


ext: ./${APP}_rozszerzony
	rm -f core.* core; echo "2i 1+3.1i 2 ? / + ?" | ./${APP}_rozszerzony


obj/main.o: src/main.cpp inc/lacze_do_gnuplota.hh inc/Bryla_geom.hh inc/Dron.hh inc/Graniastoslup.hh inc/Plaskowyz.hh inc/Gora_Dluga_Gran.hh inc/Gora_Ostry_Szczyt.hh inc/Macierz3x3.hh inc/pomocnicze.hh inc/Prostopadloscian.hh inc/Scena.hh inc/Wektor3D.hh inc/Macierz.hh inc/Wektor.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/main.o src/main.cpp

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/Bryla_geom.o: src/Bryla_geom.cpp inc/Bryla_geom.hh inc/Macierz3x3.hh inc/Wektor3D.hh inc/Macierz.hh inc/Wektor.hh inc/pomocnicze.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Bryla_geom.o src/Bryla_geom.cpp

obj/Dron.o: src/Dron.cpp inc/Dron.hh inc/Graniastoslup.hh inc/Prostopadloscian.hh inc/Bryla_geom.hh inc/Graniastoslup.hh inc/Bryla_geom.hh inc/Macierz3x3.hh inc/Wektor3D.hh inc/Macierz.hh inc/Wektor.hh inc/pomocnicze.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Dron.o src/Dron.cpp

obj/Graniastoslup.o: src/Graniastoslup.cpp inc/Graniastoslup.hh inc/Bryla_geom.hh inc/Macierz3x3.hh inc/Wektor3D.hh inc/Macierz.hh inc/Wektor.hh inc/pomocnicze.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Graniastoslup.o src/Graniastoslup.cpp

obj/Prostopadloscian.o: src/Prostopadloscian.cpp inc/Prostopadloscian.hh inc/Bryla_geom.hh inc/Macierz3x3.hh inc/Wektor3D.hh inc/Macierz.hh inc/Wektor.hh inc/pomocnicze.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Prostopadloscian.o src/Prostopadloscian.cpp

obj/Scena.o: src/Scena.cpp inc/Scena.hh src/Dron.cpp inc/Dron.hh inc/Graniastoslup.hh inc/Prostopadloscian.hh inc/Bryla_geom.hh inc/Graniastoslup.hh inc/Bryla_geom.hh inc/Macierz3x3.hh inc/Wektor3D.hh inc/Macierz.hh inc/Wektor.hh inc/pomocnicze.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Scena.o src/Scena.cpp

obj/pomocnicze.o: src/pomocnicze.cpp inc/pomocnicze.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/pomocnicze.o src/pomocnicze.cpp

obj/Wektor3D.o: src/Wektor3D.cpp inc/Wektor3D.hh inc/Wektor.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Wektor3D.o src/Wektor3D.cpp

obj/Macierz3x3.o: src/Macierz3x3.cpp inc/Macierz3x3.hh inc/Macierz.hh inc/Wektor3D.hh inc/Wektor.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Macierz3x3.o src/Macierz3x3.cpp

obj/Plaskowyz.o:  src/Plaskowyz.cpp inc/Plaskowyz.hh inc/Bryla_geom.hh inc/Macierz3x3.hh inc/Wektor3D.hh inc/Macierz.hh inc/Wektor.hh inc/pomocnicze.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Plaskowyz.o src/Plaskowyz.cpp

obj/Gora_Dluga_Gran.o:  src/Gora_Dluga_Gran.cpp inc/Gora_Dluga_Gran.hh inc/Bryla_geom.hh inc/Macierz3x3.hh inc/Wektor3D.hh inc/Macierz.hh inc/Wektor.hh inc/pomocnicze.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Gora_Dluga_Gran.o src/Gora_Dluga_Gran.cpp

obj/Gora_Ostry_Szczyt.o:  src/Gora_Ostry_Szczyt.cpp inc/Gora_Ostry_Szczyt.hh inc/Bryla_geom.hh inc/Macierz3x3.hh inc/Wektor3D.hh inc/Macierz.hh inc/Wektor.hh inc/pomocnicze.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Gora_Ostry_Szczyt.o src/Gora_Ostry_Szczyt.cpp


clean:
	rm -f obj/* ./${APP} core.* core

${TASKDIR}:
	mkdir -p ${TASKDIR}/bin.diablo ${TASKDIR}/bin.panamint

__TARGET__:
	if [ ! "${HOST}" = "diablo" ] && [ ! "${HOST}" = "panamint" ]; then exit 1; fi

export: __TARGET__ ./${APP}  ./${APP}_rozszerzony ${TASKDIR}
	mv ${APP} ${APP}_rozszerzony ${HOME}/edu/po/zad/z${TASKNO}/bin.${HOST}/

help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make ext    - tworzenie i uruchomienie aplikacji w wersji rozszerzonej"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make help   - wyswietla niniejsza informacje"
	@echo
