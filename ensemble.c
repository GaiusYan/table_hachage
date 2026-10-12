# include <stdio.h>
# include <assert.h>
# include "ensemble.h"
# include "liste_chainee.h"





/**
 * @brief Renvoie un ensemble sans élément à l'intérieur. \n
 * Le nombre d'alvéoles initial est fixé à 8.
 * La table sera allouée dynamiquement.
 * On choisira A comme un réel aléatoire entre 0.25 et 0.75. \n
 * (Ne pas oubliez de changer la graine en fonction du temps!)
 * @returns un ensemble vide
 */
Ensemble ensemble_vide() {
    Ensemble ensemble = malloc(sizeof(struct TableHachage));
    ensemble -> nb_alveoles = 8;
    ensemble -> taille = 0;
    ensemble -> A = 0.25 + (rand() / (double)RAND_MAX) * (0.75 - 0.25);
    ensemble -> table = calloc(ensemble->nb_alveoles, sizeof(ensemble -> table));
    return ensemble;
}




/**
 * @brief Donne le numéro de l'alvéole où est censée se trouver une certaine valeur. \n
 * La fonction en question est `k -> |_ A * (k & 4294967295) * nb_alveoles _| modulo nb_alveoles`.
 * Au préalable, on utilisera la fonction `objet_vers_nombre` afin de transformer
 * notre paramètre en size_t.
 * **Complexité :** O(1) (sous condition que la transformation en entier s'effectue en temps constant)
 * @param e un ensemble,
 * @param x une valeur,
 * @returns le code de hachage de x pour e.
 */
size_t alveole(Ensemble e, type_base x) {
    size_t alveole = objet_vers_nombre(e -> A * (x & 4294967295)) % (e -> nb_alveoles);
    return alveole;
}

Ensemble redimensioner(Ensemble e) {
    size_t ancienne_alveole = e -> nb_alveoles;
    size_t nouvelle_alveole = ancienne_alveole * 2;

    ListeChainee* ancien_table = e -> table;
    ListeChainee* nouvelle_table  = calloc(nouvelle_alveole,sizeof(*nouvelle_table));
    e -> nb_alveoles = nouvelle_alveole;

    for (size_t i = 0; i < ancienne_alveole; i++) {
        ListeChainee courant = e -> table[i];

        while (courant != NULL) {
            ListeChainee suivant = courant->suivant;
            size_t h = alveole(e, courant->valeur);

            nouvelle_table[h] = ajouter_debut(nouvelle_table[h], courant->valeur);
            courant = suivant;
        }
    }
    e -> table = nouvelle_table;
    free(ancien_table);

    return e;
}




/**
 * @brief Ajoute un élément dans la table de hachage. \n
 * On utilisera la fonction `alveole` pour savoir dans quelle case ajouter l'élément.
 * On s'autorisera à avoir des doublons. \n
 * Si jamais le nombre d'éléments devient supérieur à la moitié du nombre d'alvéoles,
 * on réallouera un nouvelle table de hachage où on a doublé de nombre d'alvéoles.
 * **Complexité :** O(1) (en amorti)
 * @param e un ensemble,
 * @param x une valeur qu'on veut ajouter dans e.
 */
void ajouter(Ensemble e, type_base x) {

    if (e -> taille + 1 > e -> nb_alveoles / 2) {
        e = redimensioner(e);
    }

    type_base al = alveole(e, x);
    e -> table[al] =  ajouter_debut(e -> table[al], x);
    e -> taille++;
}


