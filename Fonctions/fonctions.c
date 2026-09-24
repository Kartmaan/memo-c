#include <stdio.h>

/*  
 ============================================================================
                            FONCTIONS EN C
 ============================================================================
Une fonction est un bloc de code réutilisable qui effectue une tâche spécifique. 
Elle permet de structurer le programme en parties logiques et de réduire la 
duplication de code.

Une fonction peut prendre des paramètres (entrées) et renvoyer une valeur (sortie).
Elle peut également ne rien renvoyer (void) et ne pas prendre de paramètres.
*/

// ----------------------------------------------------
// 1. PROTOTYPES DES FONCTIONS (Déclarations)
// ----------------------------------------------------
// Indiquent au compilateur l'existence de la fonction
// avant son utilisation dans main(). Cela permet d'appeler les fonctions dans 
// n'importe quel ordre.

void afficher_bonjour(void);
int additionner(int a, int b);
float calculer_moyenne(float note1, float note2);
void reinitialiser_compteur(int *compteur); // Passage par adresse

// ----------------------------------------------------
// 2. FONCTION PRINCIPALE (main)
// ----------------------------------------------------
int main(void) {
    printf("=== 1. FONCTION SANS RETOUR (void) ===\n");
    afficher_bonjour();

    printf("\n=== 2. FONCTIONS AVEC RETOUR ET PARAMS ===\n");
    int somme = additionner(12, 8);
    printf("12 + 8 = %d\n", somme);

    float moyenne = calculer_moyenne(14.5f, 17.0f);
    printf("Moyenne : %.2f\n", moyenne);

    printf("\n=== 3. PASSAGE PAR VALEUR VS PAR ADRESSE ===\n");
    int score = 100;
    printf("Score avant réinitialisation : %d\n", score);

    // On passe l'adresse de 'score' grâce à l'opérateur &
    reinitialiser_compteur(&score);
    printf("Score après réinitialisation : %d\n", score);

    return 0;
}

// ----------------------------------------------------
// 3. DÉFINITION DES FONCTIONS
// ----------------------------------------------------
// Les fonctions sont définies après main() pour plus de clarté, mais elles pourraient aussi être définies 
// avant main() si on le souhaite.

// Fonction qui ne prend rien (void) et ne renvoie rien (void)
void afficher_bonjour(void) {
    printf("Bonjour ! Bienvenue dans le module sur les fonctions.\n");
}

// Fonction prenant 2 entiers en paramètres et renvoyant un entier
int additionner(int a, int b) {
    return a + b; // La valeur est renvoyée à l'appelant
}

// Fonction avec des flottants
float calculer_moyenne(float note1, float note2) {
    return (note1 + note2) / 2.0f;
}

// Passage par adresse : modifie directement la variable d'origine
void reinitialiser_compteur(int *compteur) {
    *compteur = 0; // Le symbole * permet d'accéder à la valeur pointée
}