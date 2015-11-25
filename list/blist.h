/*!
 * \file list.h
 * \author Louka Fraboulet
 * \brief Fichier en-tête du module `list`.
 *
 * Ce fichier en-tête contient la définition de la structure `list` et de ses fonctions de gestion :
 *  - création et destruction d'une liste ;
 *  - accès à un élément de liste ;
 *  - insertion et suppression d'un élément en début, milieu et fin de liste ;
 *  - insertion ordonnée d'un élément ;
 *  - traitement sur une liste.
 */

#ifndef LIST_H
#  define LIST_H

#  include <stdlib.h>

/*
 * \brief Renvoie le pointeur casté de `ptr`.
 *
 * Caste le pointeur `ptr` en pointeur sur `type` :
 * ((type *) ptr)
 */
#  define REF(type, ptr)		((type *) ptr)

/*
 * \brief Renvoie le pointeur casté de `ptr`.
 *
 * Caste le pointeur `ptr` en pointeur sur `type` :
 * ((type *) ptr)
 */
#  define REF_DATA(type, ptr)	((type *) (ptr)->data)

/*
 * \brief Renvoie la valeur castée de `ptr`.
 *
 * Caste le pointeur ptr en pointeur sur `type`, puis renvoie sa valeur déréférencée :
 * (*((type *) ptr))
 */
#  define DEREF(type, ptr)		(*((type *) ptr))

/*
 * \brief Renvoie la valeur castée du membre `data` de `ptr`.
 *
 * Caste le membre `data` du pointeur `ptr` en pointeur sur `type`, puis renvoie sa valeur déréférencée :
 * (*((type *) (ptr)->data))
 */
#  define DEREF_DATA(type, ptr)	(*((type *) (ptr)->data))

/*
 * \brief Renvoie un pointeur générique vers `val`.
 *
 * Récupère l'adresse de `val` puis la caste en pointeur générique :
 * ((void *) &(val))
 */
#  define TO_REF(val)				((void *) &(val))


/*!
 *
 * \struct bblist_t
 * \brief Représente un élément de liste
 *
 * Cette structure représente un élément de liste.
 */
typedef struct blist_t blist_t;
struct blist_t {
	void * data;	//!< Donnée de l'élément.

	blist_t * next;	//!< Adresse de l'élément suivant.
}; 


/*!
 * \brief "Crée" une nouvelle liste.
 * 
 , ou NULL.
 *
 * \return NULL
 * \see blist_prepend()
 * \see blist_append()
 */
blist_t *	blist_new();

/*!
 * \brief Crée une nouvelle liste avec un premier élément.
 * \param data Donnée du premier élément.
 *
 * Renvoie une nouvelle liste avec un premier élément contenant la donnée `data`.
 * Renvoie NULL si l'allocation dynamique échoue.
 *
 * \return Une liste, ou NULL s'il y a une erreur.
 */
blist_t *	blist_new_init(void * data);

/*!
 * \brief Détruit une liste.
 * \param list Liste à détruire.
 *
 * Détruit tous les éléments de la liste `list`, puis la liste elle-même.
 * ATTENTION : Ne prend pas en charge la désallocation des données de chaque élément !
 */
void		blist_delete(blist_t ** list);



/*!
 * \brief Récupère la donnée de l'élément à l'indice donné.
 * \param list Liste à traiter.
 * \param index Indice de l'élément à récupéré.
 *
 * Parcours la liste `list` jusqu'à l'indice `index`, puis renvoie la donnée de l'élément sous
 * forme de pointeur générique.
 * Si la liste est vide, renvoie NULL.
 * Si l'indice est négatif ou supérieur à la taille de la liste, renvoie NULL.
 *
 * \return Un pointeur générique, ou NULL s'il y a une erreur.
 */
void *		blist_get_at(blist_t * list, int index);

/*!
 * \brief Ecrase la donnée de l'élément à l'indice donnée.
 * \param list Liste à modifier.
 * \param index Indice de l'élément à changer.
 * \param data Nouvelle donnée.
 *
 * Parcours la liste `list` jusqu'à l'indice `index`, remplace la donnée de l'élément par la
 * nouvelle donnée, puis renvoie l'ancienne donnée sous forme de pointeur générique.
 * Si la liste est vide, renvoie NULL.
 * Si l'indice est négatif ou supérieur à la taille de la liste, renvoie NULL.
 * 
 * \return Un pointeur générique, ou NULL s'il ya une erreur.
 */ 
void *		blist_set_at(blist_t * list, int index);



/*!
 * \brief Ajoute un élément en début de liste.
 * \param list Liste à étendre.
 * \param data Donnée à mettre dans le nouvel élément.
 *
 * Ajoute un élément en début de liste en allouant un nouvel élément dans lequel on place `data`.
 * Si la liste est vide, on lui ajoute son premier élément.
 *
 * Renvoie NULL si l'allocation dynamique échoue.
 *
 * \return Le nouvel élément ajouté (donc la liste), ou NULL s'il y a une erreur.
 */
blist_t *	blist_prepend(blist_t * list, void * data);

/*!
 * \brief Ajoute un élément en fin de liste.
 * \param list Liste à étendre.
 * \param data Donnée à mettre dans le nouvel élément.
 * 
 * Même chose que list_prepend(), mais en début de liste.
 * Si la liste est vide, on lui ajoute son premier élément.
 *
 * Renvoie NULL si l'allocation dynamique échoue.
 *
 * \return Le nouvel élément ajouté (donc le dernier élément), ou NULL s'il y a une erreur.
 */
blist_t *	blist_append(blist_t * list, void * data);



/*!
 * \brief Supprime le premier élément de la liste.
 * \param list Liste à réduire.
 * 
 * Renvoie NULL si `list` vaut NULL.
 *
 * ATTENTION : Ne prend pas en charge la désallocation de la donnée dans l'élément !
 *
 * \return Donnée de l'élément retiré, ou NULL s'il y a une erreur.*
 */
void *		blist_pop_front(blist_t * list);


/*!
 * \brief Supprime le dernier élément de la liste.
 * \param list Liste à réduire.
 *
 * ATTENTION : Ne prend pas en charge la désallocation de la donnée dans l'élément !
 *
 * \return Donnée de l'élément retiré, ou NULL s'il y a une erreur.*
 */
void *		blist_pop_back(blist_t * list);



/*!
 * \brief Insère un élément dans la liste à l'indice donné.
 * \param index Indice où l'élément doit être inséré.
 * \param data Donnée de l'élément à insérer.
 *
 * \return La liste modifiée, ou NULL s'il y a une erreur.*
 */
blist_t * blist_insert_at(int index, void * data);

/*!
 * \brief Supprime de la liste l'élément à l'indice donné.
 * \param list Liste à réduire.
 * \param index Indice où l'élément doit être supprimé.
 *
 * ATTENTION : Ne prend pas en charge la désallocation de la donnée dans l'élément !
 *
 * \param list Liste à étendre.
 * \param data Donnée de l'élément à insérer.
 * \param compare Fonction de comparaison entre deux données.
 *
 * Insère un élément en supposant que `list` est ordonnée.
 * Utilise la fonction `compare` pour comparer la donnée `data` à ajouter avec la donnée de chaque
 * élément afin de choisir l'emplacement approprié pour insérer la donnée `data`.
 *
 * Le comportement attendu de la fonction `compare` doit être semblable à strcmp() :
 *  - renvoyer 0 si les deux valeurs sont égales. Sinon, si la première valeur est plus grande,
 *  renvoyer 1. Sinon renvoyer -1.
 *  - prendre deux arguments : les deux valeurs à comparer.
 *
 * \return La liste modifiée, ou NULL s'il y a une erreur.*
 */
blist_t *	blist_insert(blist_t * list, void * data, int (*compare)(void *, void *));



/*!
 * \brief Applique une fonction à tous les éléments.
 * \param list Liste à traiter.
 * \param apply Fonction à appliquer.
 *
 * Applique la fonction `apply` à chaque donnée des éléments de la liste `list`.
 *
 * Le comportement attendu de `apply` est de :
 *  - renvoyer 0 si le traitement sur la donnée de l'élément courant exige un arrêt de la fonction.
 *  - prend deux paramètres : `data`, la donnée à traiter, et `arg`, un argument quelconque.
 *
 * \return La liste modifiée, ou NULL s'il y a une erreur.*
 */
blist_t *	blist_map(blist_t * list, int (*apply)(void * data, void * arg));

#endif

