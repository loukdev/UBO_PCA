#include "blist.h"

blist_t *
blist_new()
{
	return NULL;
}

blist_t *
blist_new_init(void * data)
{
	blist_t * list = malloc(sizeof(blist_t));

	if(list)
	{
		list->data = data;
		list->next = NULL;
	}

	return list;
}

void
blist_delete(blist_t ** list)
{
	if(!list && !*list)	return;

	// Tant qu'il y a un élément suivant, on le supprime d'abord.
	if((*list)->next)
		blist_delete(& ((*list)->next));

	free(*list);	// Tous les suivants sont supprimés, on supprime le premier élément.
	*list = NULL;
}



/* En supprimant le 1er élément, on change l'adresse de list. Ce qui oblige à :
 *  - soit prendre en paramètre un pointeur de pointeur pour modifier l'adresse pointée par `list`,
 *  - soit renvoyer la nouvelle adresse.
 * Par soucis d'homogénité des arguments entre les fonctions, la 1ere solution est écartée.
 * Comme la donnée de l'élément supprimé est renvoyée, la 2e solution est écartée.
 *
 * Pour répondre aux contraintes, le traitement suivant est effectué :
 *  1. La donnée est "déplacée" (copie de pointeurs) dans le 2e ;
 *  2. Le 2e élément est supprimée.
 *  3. L'ancienne donnée est renvoyée.
 * Le résultat est le même, mais l'adresse du premier élément de la liste n'est pas changée.
 *
 * L'utilisateur possède la responsabilité en ce qui concerne la gestion de la mémoire des données.
 * Pour cette raison, ne pas renvoyer l'ancienne donnée ne pose à-priori pas de problèmes, mais ce choix a été fait par
 * soucis de souplesse, en échange d'une copie d'adresse supplémentaire.
 */
void *
blist_pop_front(blist_t * list)
{
	if(!list)	return NULL;

	// S'il n'y a qu'un seul élément, il est supprimé.
	if(!list->next)
	{
		void * data = list->data;
		blist_delete(&list);
		return data;
	}

	blist_t * next = list->next;	// On récupère l'élément à supprimer.
	void * data = list->data;		// On récupère la donnée du 1er élément.

	list->next = next->next;		// On délie le 2e élément en liant le 1er avec le 3e.
	list->data = next->data;		// On copie l'adresse de la donnée du 2e élément dans le 1er élément.
	free(list->next);

	return data;	// On renvoie la donnée de l'élément supprimé.
}

void *
blist_pop_back(blist_t * list)
{
	if(!list)	return NULL;

	blist_t * blast = NULL;		// Avant-dernier élément de la liste, NULL par défaut.
	while(list->next != NULL)	// Parcours de la liste tant qu'il y a un suivant.
	{
		blast = list;
		list = list->next;
	}

	if(blast)					// On délie le dernier élément s'il y en a un.
		blast->next = NULL;

	void * data = list->data;	// On récupère la donnée du dernier élément, cet élément est ensuite supprimé.
	free(list);

	return data;				// On renvoie la donnée de l'élément supprimé.
}



blist_t *
blist_append(blist_t * list, void * data)
{
	if(!list)
		return blist_new_init(data);

	while(list->next)
		list = list->next;

	return list->next = blist_new_init(data);
}

