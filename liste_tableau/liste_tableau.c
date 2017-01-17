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
 *  \file liste_tableau.h
 *
 *  Fichier d'implémentation contenant la structure de donnée 'liste_tableau'.
 *  Une Liste Tableau ("Array List") est une liste implémenté grâce à
 *  un tableau mémoire contiguë (array).
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste_tableau.h"

#define TAILLE_TAMPON_FICHIER 4096

/**
 * \brief Une liste implémenté de structures tableaux.
 */
struct liste_tableau_struct {
    int taille;
    int* tableau;
    int longueur_tableau;
    bool a_erreur;
    char* erreur;
};

/**
 *  \brief Alloue un espace mémoire pour y placer la liste tableau.
 *
 *  \param longueur_tableau : La longueur de la liste_tableau à allouer.
 *
 *  \return La liste tableau allouée en mémoire.
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
 *  \brief Crée une liste tableau à partir de données chargées venant
 *         d'un fichier.
 *
 *  \param nom_fichier : Le nom du fichier contenant les données à charger.
 *
 *  \return Une nouvelle liste tableau créée à l'aide des donnée contenues
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
                                              "Mémoire insuffisante.");
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
 *  \brief Détruit la liste tableau pour libérer l'espace mémoire
 *         qu'elle occupait.
 *
 *  \param liste : La liste tableau à détruire.
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
 *  \brief Sauvegarde les données contenues dans la liste tableau
 *         dans un fichier.
 *
 *  \param liste : La liste tableau à sauvegarder.
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
                                      fichier en écriture.");
    }
}

/**
 *  \brief Renvoie la taille de la liste tableau.
 *
 *  \param liste : La liste tableau à trouver sa taille.
 *
 *  \return Le nombre d'élément contenus dans la liste tableau.
 */
int taille_liste_tableau(liste_tableau* liste)
{
    retirer_erreur_liste_tableau(liste);
    return liste->longueur_tableau;
}

/**
 *  \brief Ajoute un élément à la liste tableau.
 *
 *  \param liste : La liste tableau où ajouter les éléments.
 *  \param element : L'élément à ajouter dans la liste tableau.
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
 *  \brief Renvoie l'élément à la position de l'index.
 *
 *  \param liste : La liste tableau où chercher un élément.
 *  \param index : La position de l'élément à retourner.
 *
 *  \return L'élément qui est indiqué par l'index.
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
 *  \brief Insère un élément à la position de l'index et décale toutes les
 *         autres valeurs.
 *
 *  \param liste : La liste tableau où insérer un élément.
 *  \param index : La position de l'élément à insérer.
 *  \param element : L'élément à insérer.
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
 *  \brief Remplace un élément par un autre dans la liste tableau.
 *
 *  \param liste : La liste où faire le remplacement.
 *  \param index : La position de l'élément à remplacer.
 *  \param element : L'élément qui remplacera un autre.
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
 *  \brief Retire un élément dans la liste tableau à la position souhaitée
 *         et décale toutes les autres valeurs.
 *
 *  \param liste : La liste tableau où faire la suppression d'un élément.
 *  \param index : La position de l'élément à retirer.
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
 *         la réponse (Vrai/Faux).
 *
 *  \param liste : La liste tableau à vérifier.
 *
 *  \return Vrai s'il y a erreur et Faux en cas inverse.
 */
bool a_erreur_liste_tableau(liste_tableau* liste)
{
    return liste->a_erreur;
}

/**
 *  \brief Indique ce qu'est l'erreur en la décrivant.
 *
 *  \param liste : La liste tableau qui a été vérifiée.
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
 *         celle-ci dans la librairie. Mets "a_erreur_liste_tableau" à Vrai.
 *
 *  \param liste : La liste tableau qui a été vérifiée.
 *  \param erreur : La description de l'erreur.
 */
void inscrire_erreur_liste_tableau(liste_tableau* liste, const char* erreur)
{
    liste->a_erreur = true;
    strncpy(liste->erreur, erreur, ERREUR_TAILLE);
}

/**
 *  \brief Retire l'erreur en mettant "a_errreur_liste_tableau" à Faux.
 *
 *  \param liste : La liste tableau qui a été vérifiée.
 */
void retirer_erreur_liste_tableau(liste_tableau* liste)
{
    liste->a_erreur = false;
}

/* vi: set ts=4 sw=4 expandtab: */
/* Indent style: 1TBS */
