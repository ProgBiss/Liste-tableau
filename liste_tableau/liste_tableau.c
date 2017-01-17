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
 *  \file liste_tableau.h
 *
 *  Fichier d'impl�mentation contenant la structure de donn�e 'liste_tableau'.
 *  Une Liste Tableau ("Array List") est une liste impl�ment� gr�ce �
 *  un tableau m�moire contigu� (array).
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste_tableau.h"

#define TAILLE_TAMPON_FICHIER 4096

/**
 * \brief Une liste impl�ment� de structures tableaux.
 */
struct liste_tableau_struct {
    int taille;
    int* tableau;
    int longueur_tableau;
    bool a_erreur;
    char* erreur;
};

/**
 *  \brief Alloue un espace m�moire pour y placer la liste tableau.
 *
 *  \param longueur_tableau : La longueur de la liste_tableau � allouer.
 *
 *  \return La liste tableau allou�e en m�moire.
 */
liste_tableau* creer_liste_tableau(int longueur_tableau)
{
    liste_tableau* liste_resultat;
    liste_resultat = calloc(1, sizeof(liste_tableau));
    if (liste_resultat) {
        liste_resultat->taille = longueur_tableau;
        liste_resultat->longueur_tableau = 0;
        liste_resultat->tableau = calloc(longueur_tableau, sizeof(int));
        liste_resultat->a_erreur = false;
        liste_resultat->erreur = calloc(ERREUR_TAILLE, sizeof(char));
    }
    return liste_resultat;
}

/**
 *  \brief Cr�e une liste tableau � partir de donn�es charg�es venant
 *         d'un fichier.
 *
 *  \param nom_fichier : Le nom du fichier contenant les donn�es � charger.
 *
 *  \return Une nouvelle liste tableau cr��e � l'aide des donn�e contenues
 *          dans un fichier.
 */
liste_tableau* charger_liste_tableau(char *nom_fichier)
{
    liste_tableau* liste_resultat;
    FILE *liste_fichier;
    int liste_count;
    int i;
    int *liste_tampon;
    int longueur;
    FILE* nb_element_fichier = fopen(nom_fichier, "rb");
    fseek(nb_element_fichier, 0, SEEK_END);
    longueur = ftell(nb_element_fichier) / sizeof(int);
    fseek(nb_element_fichier, 0, SEEK_SET);
    fclose(nb_element_fichier);
    liste_resultat = creer_liste_tableau(longueur);
    if (liste_resultat) {
        liste_fichier = fopen(nom_fichier, "rb");
        if(liste_fichier) {
            liste_tampon = calloc(sizeof(int), TAILLE_TAMPON_FICHIER);
            if (liste_tampon) {
                liste_count = 1;
                while (liste_count > 0) {
                    liste_count = fread(liste_tampon, sizeof(int),
                                            TAILLE_TAMPON_FICHIER,
                                            liste_fichier);
                    if (liste_count > 0) {
                        for (i = 0; i < liste_count; i = i + 1) {
                            ajouter_liste_tableau(liste_resultat,
                                                  liste_tampon[i]);
                        }
                    }
                }
            } else {
                inscrire_erreur_liste_tableau(liste_resultat,
                                              "M�moire insuffisante.");
            }
            fclose(liste_fichier);
        } else {
            inscrire_erreur_liste_tableau(liste_resultat,
                                          "Ne peux pas ouvrir le \
                                          fichier en lecture.");
        }
    }
    return liste_resultat;
}

/**
 *  \brief D�truit la liste tableau pour lib�rer l'espace m�moire
 *         qu'elle occupait.
 *
 *  \param liste : La liste tableau � d�truire.
 */
void detruire_liste_tableau(liste_tableau* liste)
{
    if (liste) {
        while (liste->taille > 0) {
            retirer_liste_tableau(liste, 0);
            liste->taille = liste->taille - 1;
        }
        if (liste->erreur) {
            free(liste->erreur);
        }
        free(liste);
    }
}

/**
 *  \brief Sauvegarde les donn�es contenues dans la liste tableau
 *         dans un fichier.
 *
 *  \param liste : La liste tableau � sauvegarder.
 *  \param nom_fichier : Le nom du fichier dans lequel sauvegarder
 *         la liste tableau.
 */
void sauvegarder_liste_tableau(liste_tableau* liste, char * nom_fichier)
{
    FILE *liste_fichier;
    int liste_restant;
    int liste_compteur;
    int liste_taille_lecture;
    int i;
    int *liste_tampon;
    retirer_erreur_liste_tableau(liste);
    liste_fichier = fopen(nom_fichier, "wb");
    if (liste_fichier) {
        liste_tampon = calloc(sizeof(int), TAILLE_TAMPON_FICHIER);
        liste_restant = taille_liste_tableau(liste);
        liste_compteur = 0;
        while (liste_restant > 0) {
            if (liste_restant > TAILLE_TAMPON_FICHIER) {
                liste_taille_lecture = TAILLE_TAMPON_FICHIER;
            } else {
                liste_taille_lecture = liste_restant;
            }
            for (i = 0; i < liste_taille_lecture; i = i + 1) {
                liste_tampon[i] = element_liste_tableau(liste, liste_compteur);
                liste_compteur = liste_compteur + 1;
            }
            fwrite(liste_tampon, sizeof(int), liste_taille_lecture,
                   liste_fichier);
            liste_restant = liste_restant - liste_taille_lecture;
        }
        fclose(liste_fichier);
    } else {
        inscrire_erreur_liste_tableau(liste, "Ne peux pas ouvrir le \
                                      fichier en �criture.");
    }
}

/**
 *  \brief Renvoie la taille de la liste tableau.
 *
 *  \param liste : La liste tableau � trouver sa taille.
 *
 *  \return Le nombre d'�l�ment contenus dans la liste tableau.
 */
int taille_liste_tableau(liste_tableau* liste)
{
    retirer_erreur_liste_tableau(liste);
    return liste->longueur_tableau;
}

/**
 *  \brief Ajoute un �l�ment � la liste tableau.
 *
 *  \param liste : La liste tableau o� ajouter les �l�ments.
 *  \param element : L'�l�ment � ajouter dans la liste tableau.
 */
void ajouter_liste_tableau(liste_tableau* liste, int element)
{
    retirer_erreur_liste_tableau(liste);
    if (liste->longueur_tableau == liste->taille) {
        liste->tableau = realloc(liste->tableau, liste->taille * 2 *sizeof(int));
        liste->taille = liste->taille * 2;
    }
    if (liste->longueur_tableau == 0) {
        liste->tableau[liste->longueur_tableau] = element;
        liste->longueur_tableau = liste->longueur_tableau + 1;
    } else {
        liste->tableau[liste->longueur_tableau - 1] = element;
        liste->longueur_tableau = liste->longueur_tableau + 1;
    }
}

/**
 *  \brief Renvoie l'�l�ment � la position de l'index.
 *
 *  \param liste : La liste tableau o� chercher un �l�ment.
 *  \param index : La position de l'�l�ment � retourner.
 *
 *  \return L'�l�ment qui est indiqu� par l'index.
 */
int element_liste_tableau(liste_tableau* liste, int index)
{
    int liste_resultat = 0;
    retirer_erreur_liste_tableau(liste);
    if (liste->taille > 0) {
        liste_resultat = liste->tableau[index];
    } else {
        inscrire_erreur_liste_tableau(liste, "La liste est vide.");
    }
    return liste_resultat;
}

/**
 *  \brief Ins�re un �l�ment � la position de l'index et d�cale toutes les
 *         autres valeurs.
 *
 *  \param liste : La liste tableau o� ins�rer un �l�ment.
 *  \param index : La position de l'�l�ment � ins�rer.
 *  \param element : L'�l�ment � ins�rer.
 */
void inserer_liste_tableau(liste_tableau* liste, int index, int element)
{
    int i;
    if (liste->taille > 0) {
        if (liste->longueur_tableau == liste->taille) {
            liste->tableau = realloc(liste->tableau, liste->taille * 2 *sizeof(int));
            liste->taille = liste->taille * 2;
        }
        if (index >= 0) {
            for (i = liste->longueur_tableau; i > index; i = i - 1) {
                liste->tableau[i + 1] = liste->tableau[i];
            }
            liste->tableau[index] = element;
        } else {
                inscrire_erreur_liste_tableau(liste, "Index non valide.");
        }
    }
}

/**
 *  \brief Remplace un �l�ment par un autre dans la liste tableau.
 *
 *  \param liste : La liste o� faire le remplacement.
 *  \param index : La position de l'�l�ment � remplacer.
 *  \param element : L'�l�ment qui remplacera un autre.
 */
void remplacer_liste_tableau(liste_tableau* liste, int index, int element)
{
    retirer_erreur_liste_tableau(liste);
    if (liste->taille > 0) {
        liste->tableau[index] = element;
    } else {
        inscrire_erreur_liste_tableau(liste, "La liste est vide.");
    }
}

/**
 *  \brief Retire un �l�ment dans la liste tableau � la position souhait�e
 *         et d�cale toutes les autres valeurs.
 *
 *  \param liste : La liste tableau o� faire la suppression d'un �l�ment.
 *  \param index : La position de l'�l�ment � retirer.
 */
void retirer_liste_tableau(liste_tableau* liste, int index)
{
    int i;
    retirer_erreur_liste_tableau(liste);
    if (liste->taille > 0) {
        for (i = liste->longueur_tableau; i < index; i = i - 1) {
            liste->tableau[index - 1] = liste->tableau[index];
        }
        liste->longueur_tableau = liste->longueur_tableau + 1;
    } else {
        inscrire_erreur_liste_tableau(liste, "La liste est vide.");
    }
}

/**
 *  \brief Cherche s'il y a une erreur dans la liste tableau et retourne
 *         la r�ponse (Vrai/Faux).
 *
 *  \param liste : La liste tableau � v�rifier.
 *
 *  \return Vrai s'il y a erreur et Faux en cas inverse.
 */
bool a_erreur_liste_tableau(liste_tableau* liste)
{
    return liste->a_erreur;
}

/**
 *  \brief Indique ce qu'est l'erreur en la d�crivant.
 *
 *  \param liste : La liste tableau qui a �t� v�rifi�e.
 *
 *  \return La description de l'erreur.
 */
char* erreur_liste_tableau(liste_tableau* liste)
{
    if (!liste->a_erreur) {
        strncpy(liste->erreur, "", ERREUR_TAILLE);
    }
    return liste->erreur;
}

/**
 *  \brief Place le message d'erreur dans la liste tableau et conserve
 *         celle-ci dans la librairie. Mets "a_erreur_liste_tableau" � Vrai.
 *
 *  \param liste : La liste tableau qui a �t� v�rifi�e.
 *  \param erreur : La description de l'erreur.
 */
void inscrire_erreur_liste_tableau(liste_tableau* liste, const char* erreur)
{
    liste->a_erreur = true;
    strncpy(liste->erreur, erreur, ERREUR_TAILLE);
}

/**
 *  \brief Retire l'erreur en mettant "a_errreur_liste_tableau" � Faux.
 *
 *  \param liste : La liste tableau qui a �t� v�rifi�e.
 */
void retirer_erreur_liste_tableau(liste_tableau* liste)
{
    liste->a_erreur = false;
}

/* vi: set ts=4 sw=4 expandtab: */
/* Indent style: 1TBS */
