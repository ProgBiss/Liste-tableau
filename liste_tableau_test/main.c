/*

    Copyright (c) 2015 Nicolas Bisson

    L'autorisation est accordée, gracieusement, à toute personne acquérant une
    copie de cette bibliothèque et des fichiers de documentation associés
    (la "Bibliothèque"), de commercialiser la Bibliothèque sans restriction,
    notamment les droits d'utiliser, de copier, de modifier, de fusionner, de
    publier, de distribuer, de sous-licencier et / ou de vendre des copies de
    la Bibliothèque, ainsi que d'autoriser les personnes auxquelles la
    Bibliothèque est fournie à le faire, sous réserve des conditions suivantes:

    La déclaration de copyright ci-dessus et la présente autorisation doivent
    être incluses dans toutes copies ou parties substantielles de la
    Bibliothèque.

    LA BIBLIOTHÈQUE EST FOURNIE "TELLE QUELLE", SANS GARANTIE D'AUCUNE SORTE,
    EXPLICITE OU IMPLICITE, NOTAMMENT SANS GARANTIE DE QUALITÉ MARCHANDE,
    D’ADÉQUATION À UN USAGE PARTICULIER ET D'ABSENCE DE CONTREFAÇON. EN AUCUN
    CAS, LES AUTEURS OU TITULAIRES DU DROIT D'AUTEUR NE SERONT RESPONSABLES DE
    TOUT DOMMAGE, RÉCLAMATION OU AUTRE RESPONSABILITÉ, QUE CE SOIT DANS LE
    CADRE D'UN CONTRAT, D'UN DÉLIT OU AUTRE, EN PROVENANCE DE, CONSÉCUTIF À OU
    EN RELATION AVEC LA BIBLIOTHÈQUE OU SON UTILISATION, OU AVEC D'AUTRES
    ÉLÉMENTS DE LA BIBLIOTHÈQUE.

*/

/**
 *  \file main.c
 *
 *  Effectue les tests de la liste tableau.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "liste_tableau.h"

/**
 * \brief Test de la liste tableau.
 */
int main()
{
    int i;
    liste_tableau* liste1;
    liste_tableau* liste2;
    liste1 = creer_liste_tableau(3);
    if(liste1)
    {
        printf("Liste creee.\n");
        ajouter_liste_tableau(liste1, 8);
        ajouter_liste_tableau(liste1, 87);
        ajouter_liste_tableau(liste1, 27);
        inserer_liste_tableau(liste1, 0, 99);
        inserer_liste_tableau(liste1, 2, 66);
        retirer_liste_tableau(liste1, 3);
        remplacer_liste_tableau(liste1, 0, 31);
        if (a_erreur_liste_tableau(liste1)) {
            printf("Ne peut remplacer l'element a l'index 3: %s\n",
                                                erreur_liste_tableau(liste1));
        }
        sauvegarder_liste_tableau(liste1, "liste_tableau_test.bin");
        detruire_liste_tableau(liste1);
        liste2 = charger_liste_tableau("liste_tableau_test.bin");
        if (liste2) {
            if (a_erreur_liste_tableau(liste2)) {
                printf("Ne peut charger le fichier 'liste_tableau_test.bin':\
                            %s\n", erreur_liste_tableau(liste2));
            } else {
                if (a_erreur_liste_tableau(liste2)) {
                    printf("Erreur lors de la sauvegarde de la liste: %s\n",
                                                erreur_liste_tableau(liste2));
                }
                remplacer_liste_tableau(liste2, 4, 76);
                if (a_erreur_liste_tableau(liste2)) {
                    printf("Ne peut remplacer l'element a l'index 4: %s\n",
                                                erreur_liste_tableau(liste2));
                }
                for(i = 0; i <= taille_liste_tableau(liste2); i = i + 1) {
                    printf("L'element a l'index %d de la liste est %d.\n", i,
                                            element_liste_tableau(liste2, i));
                }
            }
            detruire_liste_tableau(liste2);
        } else {
            printf("Une erreure s'est produite");
        }
    } else {
        printf("Une erreure s'est produite");
    }
    printf("Tous les tests ont ete executes.");
    return 0;
}
