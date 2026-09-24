#include <stdio.h>
#include <stdlib.h> // Contient rand(), srand() et RAND_MAX
#include <time.h>   // Contient time() pour initialiser la graine

/*  
 ============================================================================
                            ALEATOIRE EN C
 ============================================================================
Le langage C fournit des fonctions pour générer des nombres pseudo-aléatoires.
Les langage de programmation ne peuvent pas générer de vrais nombres aléatoires, 
mais ils utilisent des algorithmes pour produire des séquences de nombres qui 
semblent aléatoires.

- rand() : génère un entier pseudo-aléatoire entre 0 et RAND_MAX (au moins 32767).
- srand(unsigned int seed) : initialise la graine pour rand(). Si on ne l'appelle 
pas, rand() produira la même séquence à chaque exécution.
- time(NULL) : renvoie le nombre de secondes écoulées depuis le 1er janvier 1970. 
On l'utilise souvent pour initialiser la graine avec srand() afin d'obtenir des 
séquences différentes à chaque appel du programme (au moins tous les secondes).
*/

// Fonction utilitaire pour générer un entier dans un intervalle [min, max]
int generer_entier(int min, int max) {
    // Formule classique : min + rand() % (max - min + 1)
    // rand() ne renvoie qu'un entier positif pseudo-aléatoire, donc on ajuste 
    // l'intervalle avec le modulo.
    return min + rand() % (max - min + 1);
}

// Fonction utilitaire pour générer un nombre flottant dans [0.0, 1.0]
double generer_double_0_1(void) {
    return (double)rand() / RAND_MAX;
}

int main(void) {
    // ----------------------------------------------------
    // 1. INITIALISATION DE LA GRAINE (srand)
    // ----------------------------------------------------
    // 'srand' définit le point de départ de la suite pseudo-aléatoire.
    // time(NULL) renvoie le nombre de secondes écoulées depuis le 1er janvier 1970.
    // Sans cette ligne, rand() donnera EXACTEMENT la même séquence à chaque lancement !
    srand((unsigned int)time(NULL));

    printf("=== 1. CONSTANTE RAND_MAX ===\n");
    // RAND_MAX est la valeur maximale que rand() peut renvoyer (au moins 32767)
    printf("Valeur maximale renvoyee par rand() : %d\n\n", RAND_MAX);

    // ----------------------------------------------------
    // 2. TIRAGE BRUT AVEC rand()
    // ----------------------------------------------------
    printf("=== 2. TIRAGE BRUT (0 a RAND_MAX) ===\n");
    for (int i = 0; i < 3; i++) {
        printf("Tirage brut n°%d : %d\n", i + 1, rand());
    }

    // ----------------------------------------------------
    // 3. TIRAGE DANS UN INTERVALLE INT [min, max]
    // ----------------------------------------------------
    printf("\n=== 3. ENTIERS DANS UN INTERVALLE ===\n");
    
    // Exemple : Simuler 5 lancers de dés à 6 faces (entre 1 et 6)
    printf("Lancers de des (1 a 6) : ");
    for (int i = 0; i < 5; i++) {
        int de = generer_entier(1, 6);
        printf("%d ", de);
    }
    printf("\n");

    // Exemple : Nombres négatifs et positifs (-10 à 10)
    printf("Valeurs entre -10 et 10 : ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", generer_entier(-10, 10));
    }
    printf("\n\n");

    // ----------------------------------------------------
    // 4. TIRAGE DE NOMBRE À VIRGULE (FLOTTANTS)
    // ----------------------------------------------------
    printf("=== 4. FLOTTANTS (double) ===\n");

    // Flottants entre 0.0 et 1.0
    printf("Flottants entre 0.0 et 1.0 : ");
    for (int i = 0; i < 3; i++) {
        printf("%.4f ", generer_double_0_1());
    }
    printf("\n");

    // Flottants dans un intervalle spécifique [min, max] (ex: 5.0 à 10.0)
    double min_f = 5.0, max_f = 10.0;
    printf("Flottants entre %.1f et %.1f : ", min_f, max_f);
    for (int i = 0; i < 3; i++) {
        double val_f = min_f + generer_double_0_1() * (max_f - min_f);
        printf("%.2f ", val_f);
    }
    printf("\n");

    return 0;
}