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


/**
 * @brief Détermine si un élément appartient à un ensemble \n
 * **Complexité :** O(1) (en moyenne)
 * @param e un ensemble,
 * @param x une valeur qu'on recherche dans e.
 * @returns **true** si x appartient dans e, **false** sinon.
 */
bool appartient(Ensemble e, type_base x) {
    type_base al = alveole(e, x);

    ListeChainee courant = e -> table[al];
    while (courant != NULL) {
        if (courant -> valeur == x) {
            return true;
        }
        courant = courant->suivant;
    }
    return false;
}


Ensemble reduire_ensemble(Ensemble e) {
    size_t ancienne_alveole = e -> nb_alveoles;
    size_t nouvelle_alveole = (ancienne_alveole / 2) + 1;

    ListeChainee* ancienne_table = e -> table;
    ListeChainee* nouvelle_table = calloc(nouvelle_alveole, sizeof(*nouvelle_table));
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

    free(ancienne_table);
    return e;
}



/**
 * @brief Supprime une occurrence d'un élément dans la table de hachage. \n
 * Si jamais le nombre d'éléments devient inférieur au huitième du nombre d'alvéoles,
 * on réallouera un nouvelle table de hachage où on a reduit de moitié le nombre d'alvéoles
 * (sauf si le nombre d'alvéoles devient inférieur à 8). \n
 * Déclenche une erreur si jamais la valeur n'est pas dans e. \n
 * **Complexité :** O(1) (en moyenne et en amorti)
 * @param e un ensemble,
 * @param x une valeur dont on veut supprimer une occurrence dans e.
 */
void supprimer(Ensemble e, type_base x) {
    if (e -> taille == e -> nb_alveoles / 8) {
        reduire_ensemble(e);
    }

    type_base al = alveole(e, x);
    e -> table[al] = supprimer_lc(e -> table[al], x);
    e -> taille--;
}



/**
 * @brief Libère la mémoire associée à un ensemble. \n
 * On désallouera chaque liste chaînée, la table, ainsi que la structure elle-même.
 * **Complexité :** O(1)
 * @param e un ensemble.
 */
void liberer_ensemble(Ensemble e) {

    for (size_t i = 0; i < e -> nb_alveoles; i++) {
        ListeChainee courant = e -> table[i];
        while (courant != NULL) {
            ListeChainee suivant = courant -> suivant;
            free(courant);
            courant = suivant;
        }
    }
    free(e -> table);
}


/**
 * @brief Convertit un ensemble en une liste (voir TP précédent) \n
 * L'ensemble n'est pas modifié. \n
 * **Complexité :** O(taille de l'ensemble)
 * @param e un ensemble.
 * @returns une liste contenant les mêmes éléments que **e** (l'ordre n'a
 * pas d'importance).
 */
Liste ensemble_vers_liste(Ensemble e) {
    Liste liste = liste_vide();
    for (size_t i = 0; i < e -> nb_alveoles; i++) {
        ListeChainee courant = e -> table[i];

        while (courant != NULL) {
            ajouter_en_fin(liste, courant->valeur);
            courant = courant->suivant;
        }
    }
    return liste;
}

/**
 * @brief Convertit une liste en un ensemble. \n
 * La liste n'est pas modifiée. \n
 * **Complexité :** O(taille de la liste)
 * @param l une liste.
 * @returns un ensemble contenant les mêmes élements que **l**.
 */
Ensemble  liste_vers_ensemble(Liste l) {
    Ensemble e = ensemble_vide();

    for (size_t i = 0; i < longueur(l); i++) {
        int position = element(l,i);
        ajouter(e, position);
    }
    return e;
}



