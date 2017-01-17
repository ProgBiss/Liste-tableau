/*

    Copyright (c) 2015 Nicolas Bisson

    L'autorisation est accord�e, gracieusement, � toute personne acqu�rant une
    copie de cette biblioth�que et des fichiers de documentation associ�s
    (la "Biblioth�que"), de commercialiser la Biblioth�que sans restriction,
    notamment les droits d'utiliser, de copier, de modifier, de fusionner, de
    publier, de distribuer, de sous-licencier et / ou de vendre des copies de
    la Biblioth�que, ainsi que d'autoriser les personnes auxquelles la
    Biblioth�que est fournie � le faire, sous r�serve des conditions suivantes:

    La d�claration de copyright ci-dessus et la pr�sente autorisation doivent
    �tre incluses dans toutes copies ou parties substantielles de la
    Biblioth�que.

    LA BIBLIOTH�QUE EST FOURNIE "TELLE QUELLE", SANS GARANTIE D'AUCUNE SORTE,
    EXPLICITE OU IMPLICITE, NOTAMMENT SANS GARANTIE DE QUALIT� MARCHANDE,
    D�AD�QUATION � UN USAGE PARTICULIER ET D'ABSENCE DE CONTREFA�ON. EN AUCUN
    CAS, LES AUTEURS OU TITULAIRES DU DROIT D'AUTEUR NE SERONT RESPONSABLES DE
    TOUT DOMMAGE, R�CLAMATION OU AUTRE RESPONSABILIT�, QUE CE SOIT DANS LE
    CADRE D'UN CONTRAT, D'UN D�LIT OU AUTRE, EN PROVENANCE DE, CONS�CUTIF � OU
    EN RELATION AVEC LA BIBLIOTH�QUE OU SON UTILISATION, OU AVEC D'AUTRES
    �L�MENTS DE LA BIBLIOTH�QUE.

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
