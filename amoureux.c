#include "ensemble.h"
#include <assert.h>
#include <time.h>
#include <limits.h>
# include <stdio.h>


size_t fonction_nombre_amoureux_liste(Liste l) {
    size_t nombre_amoureux = 0;
    Ensemble e = liste_vers_ensemble(l);

    for (size_t i = 0 ; i < e -> nb_alveoles ; i++) {
        ListeChainee courant = e -> table[i];

        while (courant != NULL) {
            type_base moitie = courant -> valeur / 2;
            type_base modulo = courant -> valeur % 2;
            if (appartient(e,moitie) && modulo == 0) {
                nombre_amoureux++;
            }
            courant = courant -> suivant;
        }
    }
    return nombre_amoureux;
}




/**
 * @brief Permet de vérifier le bon fonctionnement et la rapidité de
 * votre fonction qui compte le nombre d'entiers amoureux.
 * Une liste de la bonne taille est tirée aléatoirement.
 * @param votre_fonction la fonction que vous avez écrit
 * (elle doit prendre une Liste en entrée et un size_t) en sortie
 * @param taille la taille de la liste tirée aléatoirement pour le test.
 */
void test_nombre_amoureux(size_t (*votre_fonction) (Liste), size_t taille ){

    // Je commence par construire une liste aléatoire de la bonne taille :
    Liste l = liste_vide();

    int base = -taille/2 + (taille/2 % 2) + 1;
    int x = base;
    size_t sol = 0;

    ajouter_en_fin(l,x);

    for(size_t i = 1; i < taille ; i++){

        if ( rand() % 2 == 0 || abs(x) > INT_MAX / 8 ) {
            base += 2*(1 + rand() % 3);
            x = base;
            if (rand() % 2 == 0 && abs(x) < INT_MAX / 8){
                x *= 2;
            }
        }
        else{
            x *= 2;
            sol++;
        }

        size_t j = rand() % (i+1);
        ajouter_en_fin(l,x);
        modifier(l,i,element(l,j));
        modifier(l,j,x);
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Je teste votre fonction ici :
    assert( votre_fonction(l) == sol );

    clock_gettime(CLOCK_MONOTONIC, &end);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Temps d'exécution (pour une taille %ld): %f secondes \n", taille, elapsed_time_ns/1000.0/1000.0/1000.0);

    liberer_liste(l);
}