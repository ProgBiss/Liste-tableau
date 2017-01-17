#######################################################################
# Script de compilation de la librairie de Liste Tableau (liste_tableau)
# Auteur: Nicolas Bisson
# Date: 2015-10-31
# License: MIT
# Inspiré de: Louis Marchand
#######################################################################

all:debug release

obj/Debug/liste_tableau.o:liste_tableau.h liste_tableau.c
	mkdir -p obj/Debug
	gcc -Wall -g -fpic -c liste_tableau.c -o $@

bin/Debug/libliste_tableau.a:obj/Debug/liste_tableau.o
	rm -f $@
	mkdir -p bin/Debug/
	ar -r -s $@ $^

bin/Debug/libliste_tableau.so:obj/Debug/liste_tableau.o
	mkdir -p bin/Debug/
	gcc -shared $^ -o $@

obj/Release/liste_tableau.o:liste_tableau.h liste_tableau.c
	mkdir -p obj/Release
	gcc -O2 -Wall -fpic  -c liste_tableau.c -o $@

bin/Release/libliste_tableau.a:obj/Release/liste_tableau.o
	rm -f $@
	mkdir -p bin/Release/
	ar -r -s $@ $^

bin/Release/libliste_tableau.so:obj/Release/liste_tableau.o
	mkdir -p bin/Release/
	gcc -shared $^ -o $@

debug_static:bin/Debug/libliste_tableau.a

debug_dynamic:bin/Debug/libliste_tableau.so

debug:debug_static debug_dynamic

release_static:bin/Release/libliste_tableau.a

release_dynamic:bin/Release/libliste_tableau.so

release:release_static release_dynamic

static: debug_static release_static

dynamic: debug_dynamic release_dynamic

clean:
	rm -rf obj
	rm -rf bin

.PHONY: all debug_static debug_dynamic debug release_static release_dynamic release static dynamic clean
