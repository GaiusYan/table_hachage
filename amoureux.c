#include "ensemble.h"



bool fonction_nombre_amoureux_ensemble(Ensemble e, type_base nombre_amoureux) {
    for (size_t i = 0; i < e -> nb_alveoles; i++) {
        if (appartient(e, (nombre_amoureux % 2 == 0)) && nombre_amoureux % 2 == 0) {
            return true;
        }
    }
    return false;
}


bool fonction_nombre_amoureux_liste(Liste l, type_base nombre_amoureux) {
    for (size_t i = 0; i < l -> taille; i++) {
        if (l -> tableau[i] == (nombre_amoureux / 2) && nombre_amoureux % 2 == 0) {
            return true;
        }
    }
    return false;
}
