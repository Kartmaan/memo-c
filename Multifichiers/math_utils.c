#include <stdio.h>
#include "math_utils.h" // On inclut notre propre fichier .h avec des guillemets ""

/*
 ============================================================================
                               FICHIER SOURCE
 ============================================================================  
Contient la définition des fonctions (l'implémentation).

Ce fichier est le « cerveau » de notre programme. Il contient le code réel qui 
sera exécuté, en utilisant les déclarations du fichier d'en-tête pour s'assurer 
que tout est correctement lié.
*/

// Implémentation de la fonction additionner
int additionner(int a, int b) {
    return a + b;
}

// Implémentation de la fonction calculer_moyenne
double calculer_moyenne(int tableau[], int taille) {
    if (taille <= 0) return 0.0;

    int somme = 0;
    for (int i = 0; i < taille; i++) {
        somme += tableau[i];
    }

    return (double)somme / taille;
}