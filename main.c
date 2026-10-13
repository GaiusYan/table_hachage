# include <stdio.h>
# include "liste_chainee.c"
# include <assert.h>
# include "amoureux.c"
#include "ensemble.c"


void afficher_liste (Liste l) {
    printf("[");
    for (int i = 0; i < (longueur(l)); i++) {
        printf("%d,", l -> tableau[i]);
    }
    printf("]\n");
}

void afficher_table_hachage(Ensemble e) {
    for (type_base i = 0; i < e ->nb_alveoles; i++) {

        printf("Element : %d", i);
        printf("\n");
        afficher_liste(liste_chainee_vers_liste(e -> table[i]));
    }
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
    //afficher_liste(liste_chainee_vers_liste(lc));


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
    ajouter(e,43);
    ajouter(e,56);
    ajouter(e,78);
    ajouter(e,89);
    ajouter(e,33);
    ajouter(e,58);
    ajouter(e,76);
    ajouter(e,21);
    ajouter(e,59);
    ajouter(e,32);
    ajouter(e,45);
    ajouter(e,6);
    ajouter(e,40);
    ajouter(e,5);
    ajouter(e,5);
    ajouter(e,9);
    ajouter(e,7);
    //afficher_table_hachage(e);
    assert(appartient(e,58));
    supprimer(e, 58);
    supprimer(e,89);
    //assert(appartient(e,89));
    supprimer(e,33);
    supprimer(e,76);
    supprimer(e,21);
    supprimer(e,59);
    supprimer(e,32);
    supprimer(e,45);
    supprimer(e,6);
    supprimer(e,40);
    supprimer(e,5);
    supprimer(e,5);
    supprimer(e,9);
    supprimer(e,7);
    //afficher_table_hachage(e);
    //liberer_ensemble(e);
    //assert(appartient(e,2));
    //afficher_liste(ensemble_vers_liste(e));

    //afficher_table_hachage(e);


    // Test table amoureux
    // Ajout des élements dans cette liste : [3,-1,8,4,18,0,9,16,-2]
    Liste l = liste_vide();
    ajouter_en_fin(l,3);
    ajouter_en_fin(l,-1);
    ajouter_en_fin(l,8);
    ajouter_en_fin(l,4);
    ajouter_en_fin(l,18);
    ajouter_en_fin(l,0);
    ajouter_en_fin(l,9);
    ajouter_en_fin(l,16);
    ajouter_en_fin(l,-2);
    assert(fonction_nombre_amoureux_liste(l,8));
    return 0;
}