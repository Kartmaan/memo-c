#include <stdio.h>
#include "math_utils.h"

/*
 ============================================================================
                               FICHIER PRINCIPAL
 ============================================================================  
Contient la fonction main() qui est le point d'entrée du programme et utilise 
les fonctions définies dans les autres fichiers.
*/

int main(void) {
    printf("=== TEST DU PROJET MULTIFICHIER ===\n");

    // Utilisation de la fonction additionner
    int resultat = additionner(15, 27);
    printf("15 + 27 = %d\n", resultat);

    // Utilisation de la fonction calculer_moyenne
    int notes[4] = {12, 16, 14, 18};
    double moyenne = calculer_moyenne(notes, 4);
    printf("Moyenne des notes : %.2f\n", moyenne);

    return 0;
}