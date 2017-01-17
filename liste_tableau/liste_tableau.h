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
 *  Fichier d'ent�te contenant la structure de donn�e 'liste_tableau'.
 *  Une Liste Tableau ("Array List") est une liste impl�ment� gr�ce �
 *  un tableau m�moire contigu� (array).
 *
 */

#ifndef LISTE_TABLEAU_H_INCLUDED
#define LISTE_TABLEAU_H_INCLUDED

#include <stdbool.h>

#define ERREUR_TAILLE 255

/**
 *  \brief Une liste impl�ment� � l'aide de tableau.
 */
typedef struct liste_tableau_struct liste_tableau;

/**
 *  \brief Alloue un espace m�moire pour y placer la liste tableau.
 *
 *  \param longueur_tableau : La longueur de la liste_tableau � allouer.
 *
 *  \return La liste tableau allou�e en m�moire.
 */
liste_tableau* creer_liste_tableau(int longueur_tableau);

/**
 *  \brief Cr�e une liste tableau � partir de donn�es charg�es venant
 *         d'un fichier.
 *
 *  \param nom_fichier : Le nom du fichier contenant les donn�es � charger.
 *
 *  \return Une nouvelle liste tableau cr��e � l'aide des donn�e contenues
 *          dans un fichier.
 */
liste_tableau* charger_liste_tableau(char *nom_fichier);

/**
 *  \brief D�truit la liste tableau pour lib�rer l'espace m�moire
 *         qu'elle occupait.
 *
 *  \param liste : La liste tableau � d�truire.
 */
void detruire_liste_tableau(liste_tableau* liste);

/**
 *  \brief Sauvegarde les donn�es contenues dans la liste tableau
 *         dans un fichier.
 *
 *  \param liste : La liste tableau � sauvegarder.
 *  \param nom_fichier : Le nom du fichier dans lequel sauvegarder
 *         la liste tableau.
 */
void sauvegarder_liste_tableau(liste_tableau* liste, char * nom_fichier);

/**
 *  \brief Renvoie la taille de la liste tableau.
 *
 *  \param liste : La liste tableau � trouver sa taille.
 *
 *  \return Le nombre d'�l�ment contenus dans la liste tableau.
 */
int taille_liste_tableau(liste_tableau* liste);

/**
 *  \brief Ajoute un �l�ment � la liste tableau.
 *
 *  \param liste : La liste tableau o� ajouter les �l�ments.
 *  \param element : L'�l�ment � ajouter dans la liste tableau.
 */
void ajouter_liste_tableau(liste_tableau* liste, int element);

/**
 *  \brief Renvoie l'�l�ment � la position de l'index.
 *
 *  \param liste : La liste tableau o� chercher un �l�ment.
 *  \param index : La position de l'�l�ment � retourner.
 *
 *  \return L'�l�ment qui est indiqu� par l'index.
 */
int element_liste_tableau(liste_tableau* liste, int index);

/**
 *  \brief Ins�re un �l�ment � la position de l'index et d�cale toutes les
 *         autres valeurs.
 *
 *  \param liste : La liste tableau o� ins�rer un �l�ment.
 *  \param index : La position de l'�l�ment � ins�rer.
 *  \param element : L'�l�ment � ins�rer.
 */
void inserer_liste_tableau(liste_tableau* liste, int index, int element);

/**
 *  \brief Remplace un �l�ment par un autre dans la liste tableau.
 *
 *  \param liste : La liste o� faire le remplacement.
 *  \param index : La position de l'�l�ment � remplacer.
 *  \param element : L'�l�ment qui remplacera un autre.
 */
void remplacer_liste_tableau(liste_tableau* liste, int index, int element);

/**
 *  \brief Retire un �l�ment dans la liste tableau � la position souhait�e
 *         et d�cale toutes les autres valeurs.
 *
 *  \param liste : La liste tableau o� faire la suppression d'un �l�ment.
 *  \param index : La position de l'�l�ment � retirer.
 */
void retirer_liste_tableau(liste_tableau* liste, int index);

/**
 *  \brief Cherche s'il y a une erreur dans la liste tableau et retourne
 *         la r�ponse (Vrai/Faux).
 *
 *  \param liste : La liste tableau � v�rifier.
 *
 *  \return Vrai s'il y a erreur et Faux en cas inverse.
 */
bool a_erreur_liste_tableau(liste_tableau* liste);

/**
 *  \brief Indique ce qu'est l'erreur en la d�crivant.
 *
 *  \param liste : La liste tableau qui a �t� v�rifi�e.
 *
 *  \return La description de l'erreur.
 */
char* erreur_liste_tableau(liste_tableau* liste);

/**
 *  \brief Place le message d'erreur dans la liste tableau et conserve
 *         celle-ci dans la librairie. Mets "a_erreur_liste_tableau" � Vrai.
 *
 *  \param liste : La liste tableau qui a �t� v�rifi�e.
 *  \param erreur : La description de l'erreur.
 */
void inscrire_erreur_liste_tableau(liste_tableau* liste, const char* erreur);

/**
 *  \brief Retire l'erreur en mettant "a_errreur_liste_tableau" � Faux.
 *
 *  \param liste : La liste tableau qui a �t� v�rifi�e.
 */
void retirer_erreur_liste_tableau(liste_tableau* liste);

#endif // LISTE_TABLEAU_H_INCLUDED

/* vi: set ts=4 sw=4 expandtab: */
