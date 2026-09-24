#include <stdio.h>

/*  
 ============================================================================
                            TABLEAUX EN C
 ============================================================================
Les tableaux sont des structures de données qui permettent de stocker plusieurs 
valeurs du même type sous un même nom. 
Ils sont définis par un type (int, float, char, etc.) et une taille fixe. 
Le type détermine la nature des données que le tableau peut contenir et la quantité 
de mémoire allouée pour chaque élément.
*/

// Prototype de fonction : un tableau passé en paramètre nécessite sa taille
void afficher_tableau(int tab[], int taille);

int main(void) {
    // ----------------------------------------------------
    // TABLEAU À UNE DIMENSION
    // ----------------------------------------------------
    printf("=== 1. TABLEAU À UNE DIMENSION ===\n");

    // Déclaration et initialisation
    // Remarque : un tableau de taille 5 a des indices allant de 0 à 4
    int notes[5] = {12, 15, 8, 19, 14};

    // Modification d'un élément (l'accès se fait par l'indice [i])
    notes[2] = 10; // Remplace 8 par 10

    // Parcours et affichage avec une boucle for
    for (int i = 0; i < 5; i++) {
        printf("Note [%d] = %d\n", i, notes[i]);
    }

    // ----------------------------------------------------
    // CALCUL D'UNE MOYENNE (Cas d'usage classique)
    // ----------------------------------------------------
    printf("\n=== 2. CALCUL SUR UN TABLEAU ===\n");

    int somme = 0;
    for (int i = 0; i < 5; i++) {
        somme += notes[i];
    }
    float moyenne = (float)somme / 5; // Cast en float pour éviter la division entière
    printf("Moyenne de la classe : %.2f\n", moyenne);

    // ----------------------------------------------------
    // TABLEAU À DEUX DIMENSIONS (MATRICE)
    // ----------------------------------------------------
    printf("\n=== 3. MATRICE (2D) ===\n");

    // Grille de 2 lignes et 3 colonnes : [lignes][colonnes]
    int grille[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // Parcours à l'aide de deux boucles imbriquées
    for (int l = 0; l < 2; l++) {
        for (int c = 0; c < 3; c++) {
            printf("%d ", grille[l][c]);
        }
        printf("\n"); // Retour à la ligne après chaque ligne de la grille
    }

    // ----------------------------------------------------
    // PASSAGE D'UN TABLEAU À UNE FONCTION
    // ----------------------------------------------------
    printf("\n=== 4. AFFICHAGE VIA UNE FONCTION ===\n");
    afficher_tableau(notes, 5);

    return 0;
}

// ----------------------------------------------------
// DÉFINITION DE LA FONCTION
// ----------------------------------------------------
// En C, un tableau est automatiquement transmis par adresse (pointeur vers le 1er élément).
// Il faut donc toujours passer sa taille en paramètre séparé.
void afficher_tableau(int tab[], int taille) {
    printf("[ ");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tab[i]);
    }
    printf("]\n");
}