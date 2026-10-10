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
    type_base valeur = l -> valeur;
    while (valeur) {
        free(l -> suivant);
        valeur = l -> suivant -> valeur;
    }
}