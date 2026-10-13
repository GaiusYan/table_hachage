# include <stdio.h>
# include "liste_chainee.h"



/**
 * @brief Renvoie une liste chaînée sans élément \n
 * **Complexité :** O(1)
 * @returns une liste chaînée vide
 */
ListeChainee liste_chainee_vide() {
   return NULL;
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
    ListeChainee nouvelle_liste_chainee = malloc(sizeof(*nouvelle_liste_chainee));

    if (nouvelle_liste_chainee == NULL) {
        exit(-1);
    }

    if (l == NULL) {
        l = malloc(sizeof(*l)) ;
        l -> valeur = x;
        l -> suivant = NULL;
    } else {
        nouvelle_liste_chainee -> valeur = l -> valeur;
        nouvelle_liste_chainee -> suivant = l -> suivant;
        l -> valeur = x;
        l -> suivant = nouvelle_liste_chainee;
    }
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

    if (courant != NULL) {

        precedent -> suivant = courant -> suivant;
    }
    free(courant);
    return l;
}



/**
 * @brief Supprime le premier noeud de la chaîne et renvoie sa valeur. \n
 * La mémoire allouée pour ce premier noeud est également libérée. \n
 * **Complexité :** O(1)
 * @param adr_l, pointeur vers une liste chaînée supposée non nulle.
 * La liste pointée par adr_l est modifiée de sorte à ce que l'élément de
 * tête soit supprimé.
 * @returns la valeur du premier noeud de la liste pointée par adr_l.
 */
type_base extraire_premier(ListeChainee* adr_l) {
    ListeChainee premier_element = *adr_l;
    type_base valeur = premier_element -> valeur;

    *adr_l = premier_element -> suivant;
    free(premier_element);
    return valeur;
}



/**
 * @brief Convertit une liste chaînée en une liste (voir TP précédent). \n
 * La liste chaînée n'est pas modifiée. \n
 * **Complexité :** O(taille de la liste chaînée)
 * @param l une liste chaînée.
 * @returns une liste qui contient les mêmes éléments que **l**.
 */
Liste liste_chainee_vers_liste(ListeChainee l) {

    Liste liste = liste_vide();

    while (l != NULL) {
        ajouter_en_fin(liste, l -> valeur);
        l = l -> suivant;
    }
    return liste;
}