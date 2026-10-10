# include <stdio.h>
# include "liste_chainee.c"
# include <assert.h>

int main() {
    ListeChainee lc = liste_chainee_vide();
    ajouter_debut(lc,5);
    assert(lc -> valeur == 5);
    ajouter_debut(lc,4);
    ajouter_debut(lc,9);
    ajouter_debut(lc,10);
    ajouter_debut(lc,16);
    ajouter_debut(lc,89);
    ajouter_debut(lc,7);
    assert(lc -> valeur == 7);
    //liberer_liste_chainee(lc);
    //assert(lc == NULL);
    assert(rechercher_lc(lc, 89) == lc -> suivant);
    supprimer_lc(lc, 10);
    assert(rechercher_lc(lc, 10) == NULL);
    return 0;
}