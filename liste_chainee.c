# include <stdio.h>
# include "liste_chainee.h"



/**
 * @brief Renvoie une liste chaînée sans élément \n
 * **Complexité :** O(1)
 * @returns une liste chaînée vide
 */
ListeChainee liste_chainee_vide() {
    ListeChainee l = malloc(sizeof(struct Noeud));
    l -> suivant = NULL;
    return l;
}



/**
 * @brief Insère un noeud au début d'une liste chaînée.\n
 * Ce nouveau noeud est alloué de manière dynamique.
 * Les autres noeuds gardent la même adresse. (pas de duplication)\n
 * **Complexité :** O(1)
 * @param l liste chaînée,
 * @param x valeur qu'on veut ajouter au début de la liste,
 * @returns une liste dont le premier noeud est étiqueté par x, et dont
 * la suite est donnée par l.
 */
ListeChainee ajouter_debut(ListeChainee l, type_base x) {
    ListeChainee nouvelle_liste_chainee = liste_chainee_vide();

    nouvelle_liste_chainee -> valeur = l -> valeur;
    nouvelle_liste_chainee -> suivant = l -> suivant;
    l -> valeur = x;
    l -> suivant = nouvelle_liste_chainee;
    return l;
}




/**
 * @brief Libére chaque noeud de la liste chaînée. \n
 * **Complexité :** O(taille de la liste)
 * @param l liste chaînée.
 */
void liberer_liste_chainee(ListeChainee l) {
    while (l != NULL) {
        ListeChainee tmp = l;
        l = l -> suivant;
        free(tmp);
    }
}




/**
 * @brief Renvoie l'adresse du noeud avec une valeur donnée dans une liste chaînée. \n
 * La fonction renvoie un pointeur nul si jamais l'élément
 * n'appartient pas dans la liste.
 * On pourra ainsi tester si une valeur **x** est dans la liste chaînée **l**
 * avec la condition `if (rechercher_lc(l,x))` \n
 * **Complexité :** O(taille de la liste)
 * @param l liste chaînée,
 * @param x valeur de l'élément qu'on souhaite trouver dans l.
 * @returns un pointeur sur x si x appartient à l ; NULL dans le contraire.
 */
ListeChainee rechercher_lc(ListeChainee l, type_base x) {

    while (l != NULL) {
        if (l -> valeur == x) {
            return l;
        }
        l = l -> suivant;
    }
    return NULL;
}


/**
 * @brief Supprime une occurrence d'une valeur dans une liste chaînée. \n
 * La mémoire associée au noeud supprimé est libérée.
 * Les autres noeuds gardent la même adresse (aucun nouveau noeud n'est créé). \n
 * Si la valeur n'est pas dans la liste chaînée, déclenche une erreur. \n
 * **Complexité :** O(taille de la liste)
 * @param l liste chaînée,
 * @param x valeur dont on souhaite supprimer une occurrence dans l.
 * @returns l dans laquelle on a supprimé un noeud de valeur x (s'il existe).
 */
ListeChainee supprimer_lc(ListeChainee l, type_base x) {

    if (rechercher_lc(l, x) == NULL) {
        exit(-1);
    }

    ListeChainee precedent = l;
    ListeChainee courant = l -> suivant;

    while (courant != NULL && courant -> valeur != x) {
        precedent = courant;
        courant = courant -> suivant;
    }

    precedent -> suivant = courant -> suivant;
    free(courant);
    return l;
}



