##########################################################################
# Script de compilation du programme de test de la librairie Liste Tableau
# Auteur: Nicolas Bisson
# Date: 2015-10-31
# License: MIT
# Inspiré de: Louis Marchand
##########################################################################

UNAME=$(shell uname)

SUFIX=.exe
ifeq ($(UNAME), Linux)
SUFIX=
endif
ifeq ($(UNAME), Solaris)
SUFIX=
endif
ifeq ($(UNAME), Darwin)
SUFIX=
endif

all:debug release

obj/Debug/main.o:main.c ../liste_tableau/liste_tableau.h
	mkdir -p obj/Debug
	gcc -Wall -g -I../liste_tableau -c main.c -o $@

bin/Debug/liste_tableau_test$(SUFIX):obj/Debug/main.o ../liste_tableau/bin/Debug/libliste_tableau.a
	mkdir -p bin/Debug/
	gcc  -o $@ $^

obj/Release/main.o:main.c ../liste_tableau/liste_tableau.h
	mkdir -p obj/Release
	gcc -Wall -O2 -I../liste_tableau  -c main.c -o $@

bin/Release/liste_tableau_test$(SUFIX):obj/Release/main.o ../liste_tableau/bin/Release/libliste_tableau.a
	mkdir -p bin/Release/
	gcc -s -o $@ $^

debug: bin/Debug/liste_tableau_test$(SUFIX)

release: bin/Release/liste_tableau_test$(SUFIX)

clean:
	rm -rf obj
	rm -rf bin

.PHONY: all debug release clean
