# include <stdio.h>
# include "liste_chainee.c"
# include <assert.h>

#include "ensemble.c"


void afficher_liste (Liste l) {
    printf("[");
    for (int i = 0; i < (longueur(l)); i++) {
        printf("%d,", l -> tableau[i]);
    }
    printf("]\n");
}



int main() {
    ListeChainee lc = liste_chainee_vide();
    lc = ajouter_debut(lc,5);
    assert(lc -> valeur == 5);
    lc = ajouter_debut(lc,4);
    lc = ajouter_debut(lc,9);
    lc = ajouter_debut(lc,10);
    lc = ajouter_debut(lc,16);
    lc = ajouter_debut(lc,89);
    lc = ajouter_debut(lc,7);
    assert(lc -> valeur == 7);
    //liberer_liste_chainee(lc);
    //assert(lc == NULL);
    assert(rechercher_lc(lc, 89) == lc -> suivant);
    supprimer_lc(lc, 10);
    assert(rechercher_lc(lc, 10) == NULL);
    extraire_premier(&lc);
    assert(rechercher_lc(lc, 7) == NULL);
    afficher_liste(liste_chainee_vers_liste(lc));


    // ensemble
    Ensemble e = ensemble_vide();
    assert(e);
    ajouter(e,5);
    ajouter(e,2);
    assert(e -> table[1] -> valeur == 5);
    ajouter(e,4);
    ajouter(e,6);
    assert(e -> table[1] -> valeur == 6);
    ajouter(e,7);
    ajouter(e,8);
    assert(e -> table[0] -> valeur == 2);
    ajouter(e,14);
    ajouter(e,10);
    ajouter(e,37);
    return 0;
}