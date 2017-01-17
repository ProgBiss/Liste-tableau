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
 *  Fichier d'entête contenant la structure de donnée 'liste_tableau'.
 *  Une Liste Tableau ("Array List") est une liste implémenté grâce à
 *  un tableau mémoire contiguë (array).
 *
 */

#ifndef LISTE_TABLEAU_H_INCLUDED
#define LISTE_TABLEAU_H_INCLUDED

#include <stdbool.h>

#define ERREUR_TAILLE 255

/**
 *  \brief Une liste implémenté à l'aide de tableau.
 */
typedef struct liste_tableau_struct liste_tableau;

/**
 *  \brief Alloue un espace mémoire pour y placer la liste tableau.
 *
 *  \param longueur_tableau : La longueur de la liste_tableau à allouer.
 *
 *  \return La liste tableau allouée en mémoire.
 */
liste_tableau* creer_liste_tableau(int longueur_tableau);

/**
 *  \brief Crée une liste tableau à partir de données chargées venant
 *         d'un fichier.
 *
 *  \param nom_fichier : Le nom du fichier contenant les données à charger.
 *
 *  \return Une nouvelle liste tableau créée à l'aide des donnée contenues
 *          dans un fichier.
 */
liste_tableau* charger_liste_tableau(char *nom_fichier);

/**
 *  \brief Détruit la liste tableau pour libérer l'espace mémoire
 *         qu'elle occupait.
 *
 *  \param liste : La liste tableau à détruire.
 */
void detruire_liste_tableau(liste_tableau* liste);

/**
 *  \brief Sauvegarde les données contenues dans la liste tableau
 *         dans un fichier.
 *
 *  \param liste : La liste tableau à sauvegarder.
 *  \param nom_fichier : Le nom du fichier dans lequel sauvegarder
 *         la liste tableau.
 */
void sauvegarder_liste_tableau(liste_tableau* liste, char * nom_fichier);

/**
 *  \brief Renvoie la taille de la liste tableau.
 *
 *  \param liste : La liste tableau à trouver sa taille.
 *
 *  \return Le nombre d'élément contenus dans la liste tableau.
 */
int taille_liste_tableau(liste_tableau* liste);

/**
 *  \brief Ajoute un élément à la liste tableau.
 *
 *  \param liste : La liste tableau où ajouter les éléments.
 *  \param element : L'élément à ajouter dans la liste tableau.
 */
void ajouter_liste_tableau(liste_tableau* liste, int element);

/**
 *  \brief Renvoie l'élément à la position de l'index.
 *
 *  \param liste : La liste tableau où chercher un élément.
 *  \param index : La position de l'élément à retourner.
 *
 *  \return L'élément qui est indiqué par l'index.
 */
int element_liste_tableau(liste_tableau* liste, int index);

/**
 *  \brief Insère un élément à la position de l'index et décale toutes les
 *         autres valeurs.
 *
 *  \param liste : La liste tableau où insérer un élément.
 *  \param index : La position de l'élément à insérer.
 *  \param element : L'élément à insérer.
 */
void inserer_liste_tableau(liste_tableau* liste, int index, int element);

/**
 *  \brief Remplace un élément par un autre dans la liste tableau.
 *
 *  \param liste : La liste où faire le remplacement.
 *  \param index : La position de l'élément à remplacer.
 *  \param element : L'élément qui remplacera un autre.
 */
void remplacer_liste_tableau(liste_tableau* liste, int index, int element);

/**
 *  \brief Retire un élément dans la liste tableau à la position souhaitée
 *         et décale toutes les autres valeurs.
 *
 *  \param liste : La liste tableau où faire la suppression d'un élément.
 *  \param index : La position de l'élément à retirer.
 */
void retirer_liste_tableau(liste_tableau* liste, int index);

/**
 *  \brief Cherche s'il y a une erreur dans la liste tableau et retourne
 *         la réponse (Vrai/Faux).
 *
 *  \param liste : La liste tableau à vérifier.
 *
 *  \return Vrai s'il y a erreur et Faux en cas inverse.
 */
bool a_erreur_liste_tableau(liste_tableau* liste);

/**
 *  \brief Indique ce qu'est l'erreur en la décrivant.
 *
 *  \param liste : La liste tableau qui a été vérifiée.
 *
 *  \return La description de l'erreur.
 */
char* erreur_liste_tableau(liste_tableau* liste);

/**
 *  \brief Place le message d'erreur dans la liste tableau et conserve
 *         celle-ci dans la librairie. Mets "a_erreur_liste_tableau" à Vrai.
 *
 *  \param liste : La liste tableau qui a été vérifiée.
 *  \param erreur : La description de l'erreur.
 */
void inscrire_erreur_liste_tableau(liste_tableau* liste, const char* erreur);

/**
 *  \brief Retire l'erreur en mettant "a_errreur_liste_tableau" à Faux.
 *
 *  \param liste : La liste tableau qui a été vérifiée.
 */
void retirer_erreur_liste_tableau(liste_tableau* liste);

#endif // LISTE_TABLEAU_H_INCLUDED

/* vi: set ts=4 sw=4 expandtab: */
