#include "liste.h"
#include <stdlib.h>
#include <stdio.h>


size_t longueur(Liste l) {
	return l->taille;
}
// À vous de compléter le reste !


size_t double_capacite (size_t capacite){
	return capacite * 2;
}




/**
 * @brief Renvoie une liste sans élément.
 * Par défaut, la capacité est fixée à 8 et on double la capacité à
 * chaque réallocation. \n
 * Complexité : O(1)
 * @returns une liste vide. */
Liste liste_vide() {

	Liste l = malloc(sizeof(struct TableauDynamique));
	l -> taille = 0;
	l -> capacite = 8;
	l -> fonction_calcul_capacite = double_capacite;
	l -> tableau = malloc(8 * sizeof (size_t));
	return l;
}





/**
 * @brief Désalloue la mémoire associée à la liste
 * Désalloue le tableau et la structure elle-même.
 * Complexité : O(1)
 * @param l liste */
void liberer_liste(Liste l) {
	free(l -> tableau);
	free(l);
}


/**
 * @brief Ajoute un élément à la fin de la liste `l`.
 * Un équivalent de append en python. \n
 * Complexité **amortie** : O(1)
 * @param l liste,
 * @param x élément à ajouter à la fin.
 *
 *
 */
void ajouter_en_fin(Liste l, type_base x) {
	if (l -> taille  == l -> capacite) {
		l -> capacite = 2 * l -> capacite;
		l -> tableau = realloc(l -> tableau, (l -> capacite) * sizeof (struct TableauDynamique));
	}
	l -> tableau[l -> taille] = x;
	l -> taille++;
}



/**
 * @brief Supprime le dernier élément de la liste `l`.
 * Provoque une erreur s'il n'y pas d'éléments dans la liste. \n
 * Complexité (non amortie): O(1)
 * @param l liste.
 */
void supprimer_dernier(Liste l) {
	if (longueur(l) <= 0) {
		printf("La liste est vide\n");
		exit(1);
	}
	l -> taille--;
}


/**
 * @brief Renvoie l'élement d'une liste à une position donnée.
 * Si `pos` est négatif, alors il désigne le (-pos)-ième élément
 * en partant de la fin.
 * Déclenche une erreur si la position n'est pas dans les bornes de la liste. \n
 * L'équivalent en python simplement de `l[pos]`. \n
 * Complexité : O(1)
 * @param l liste,
 * @param pos index de l'élement à renvoyer (nombre négatif possible)
 * @returns l'élement qui se situe à l'index `pos`.
 */
type_base element(Liste l, int pos) {

	if (pos < 0) {
		// renvoyer le (-pos)-ième élément en partant de la fin.
		pos = (type_base) longueur(l) + pos;
	}

	if (l -> taille <= pos) {
		printf("La position ne correspond aux bornes de la liste\n");
		exit(1);
	}

	return l -> tableau[pos];
}





/**
 * @brief Modifie l'élement d'une liste à une position donnée.
 * Équivalent de `l[pos] = nouvelle_valeur`. \n
 * Provoque une erreur si la position n'est pas dans les bornes de la liste. \n
 * Complexité : O(1)
 * @param l liste,
 * @param pos index de l'élément à modifier.
 * @param nouvelle_valeur ce par quoi on veut remplacer la valeur.
 */
void modifier(Liste l, int pos, type_base nouvelle_valeur) {

	if (l -> taille <= pos) {
		printf("La position ne correspond aux bornes de la liste\n");
		exit(1);
	}
	l -> tableau[pos] = nouvelle_valeur;
}


/**
 * @brief Échange deux éléments d'une liste étant données leurs positions. \n
 * Équivalent pythonesque de `l[pos1],l[pos2] = l[pos2],l[pos1]`. \n
 * Provoque une erreur si une des positions n'est pas dans les bornes de la liste. \n
 * **Complexité :** O(1)
 * @param l liste,
 * @param pos1 index du premier élément dont on souhaite changer la position,
 * @param pos2 index du second élément dont on souhaite changer la position.
 */
void echanger(Liste l, int pos1, int pos2) {
	if ((int)l -> taille <= pos1 || (int)l -> taille <= pos2) {
		printf("La position ne correspond aux bornes de la liste\n");
		exit(1);
	}
	int tmp = 0;
	tmp = l -> tableau[pos1];
	l -> tableau[pos1] = l -> tableau[pos2];
	l -> tableau[pos2] = tmp;
}


/**
 * @brief Renvoie l'adresse d'un élément dans un liste.
 * La fonction renvoie un pointeur nul si jamais l'élément
 * n'appartient pas dans la liste. \n
 * Complexité : O(taille de la liste)
 * @param l liste,
 * @param x valeur de l'élément qu'on souhaite trouver dans l.
 * @returns un pointeur sur x si x appartient à l ; NULL dans le contraire.
 */
type_base* rechercher(Liste l, type_base x) {
	for (int i = 0; i <= (int)longueur(l) - 1; i++) {
		if (l -> tableau[i] == x) {
			return &l -> tableau[i];
		}
	}
	return NULL;
}


/**
 * @brief Insère un élément dans la liste à une position donnée.
 * L'équivalent en python de `l.insert(pos,x). \n
 * Provoque une erreur si la position n'est pas dans les bornes de la liste. \n
 * Complexité : O(taille de la liste)
 * @param l liste,
 * @param pos index à laquelle il faut insérer l'élément,
 * @param x valeur de l'élément à insérer.
 */
void inserer(Liste l, int pos, type_base x) {
	if ((int)l -> taille <= pos) {
		printf("La position ne correspond aux bornes de la liste\n");
		exit(1);
	}

	if (l -> taille == l -> capacite) {
		l -> capacite = 2 * l -> capacite;
		l -> tableau = realloc(l -> tableau, (l -> capacite) * sizeof (struct TableauDynamique));
	}

	for (int i = (int)l->taille; i > pos; i--) {
		l -> tableau[i] = l -> tableau[i - 1];
	}

	l -> tableau[pos] = x;
	l -> taille++;
}


/**
 * @brief Supprime toute occurrence d'un élément d'une liste. \n
 * Complexité : O(taille de la liste) \n
 * @param l liste
 * @param x la valeur qui ne doit plus apparaître dans la nouvelle liste
 */
void supprime_element(Liste l, type_base x) {
	if (l -> taille <= 0) {
		printf("La liste est vide\n");
		exit(1);
	}

	size_t nouvelle_taille = 0;

	for (int i = 0; i <= (int)longueur(l) - 1; i++) {
		if (l -> tableau[i] != x) {
			l -> tableau[nouvelle_taille] = l -> tableau[i];
			nouvelle_taille++;
		}
	}
	l->taille = nouvelle_taille;
}




/**
 * @brief Trie sur place la liste donnée en argument. \n
 * On supposera que les opérateurs < et > sont natifs
 * pour les éléments de type `type_base`. \n
 * Complexité : O( n log(n) ) où $n$ est la taille de la liste
 * @param l liste
 */
void trier(Liste l) {
	for (int i = 0; i <= (int)longueur(l) - 1; i++) {
		size_t minimum = i;
		for (int j = i + 1; j <= (int)longueur(l); j++) {
			if ( l-> tableau[j] < l -> tableau[minimum]) {
				minimum = j;
			}
		}

		if ((int)minimum != i) {
			type_base tmp = 0;
			tmp = l -> tableau[i];
			l -> tableau[i] = l -> tableau[minimum];
			l -> tableau[minimum] = tmp;
		}
	}
}
