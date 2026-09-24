#include <stdio.h>

/*  
 ============================================================================
                            BOUCLES EN C
 ============================================================================
Les boucles en C permettent de répéter un bloc de code plusieurs fois.
Il existe trois types de boucles principales : for, while et do-while.
*/

int main(void) {
    // ----------------------------------------------------
    // LA BOUCLE FOR (Répétition avec compteur connu)
    // ----------------------------------------------------
    // Syntaxe : for (initialisation; condition; incrémentation)
    printf("=== 1. BOUCLE FOR ===\n");

    // Tant que i est inférieur ou égal à 5, on répète le bloc de code.
    // i démarre à 1 et est incrémenté de 1 à chaque tour.
    // i n'a pas besoin d'être déclaré en dehors de la boucle, il est local à la boucle.
    for (int i = 1; i <= 5; i++) {
        printf("Tour n°%d\n", i);
    }

    // Décompte (pas de 2)
    printf("\nDécompte :\n");
    for (int i = 10; i >= 0; i -= 2) {
        printf("%d... ", i);
    }
    printf("Décollage !\n");

    // ----------------------------------------------------
    // LA BOUCLE WHILE (Répétition sous condition)
    // ----------------------------------------------------
    // Évalue la condition AVANT chaque exécution.
    printf("\n=== 2. BOUCLE WHILE ===\n");

    int compteur = 3;
    while (compteur > 0) {
        printf("Reste : %d\n", compteur);
        compteur--; // Ne pas oublier de modifier la variable de contrôle sinon la boucle sera infinie !
    }

    // ----------------------------------------------------
    // LA BOUCLE DO-WHILE (Exécution au moins UNE fois)
    // ----------------------------------------------------
    // Évalue la condition APRÈS la première exécution.
    // Très utile pour valider une saisie utilisateur.
    printf("\n=== 3. BOUCLE DO-WHILE ===\n");

    int reponse = 0;
    do {
        // Simule une demande où l'utilisateur doit entrer 42
        printf("Saisissez le nombre secret (42) : ");
        reponse = 42; // Simulation de la saisie
        printf("%d\n", reponse);
    } while (reponse != 42);

    printf("Code correct !\n");

    // ----------------------------------------------------
    // INSTRUCTIONS DE CONTRÔLE (break et continue)
    // ----------------------------------------------------
    printf("\n=== 4. BREAK ET CONTINUE ===\n");

    for (int i = 1; i <= 10; i++) {
        if (i == 3) {
            // 'continue' passe directement au tour suivant sans exécuter la suite
            printf("(Saut de 3) ");
            continue;
        }

        if (i == 7) {
            // 'break' interrompt et quitte immédiatement la boucle
            printf("\nInterruption à %d !", i);
            break;
        }

        printf("%d ", i);
    }
    printf("\n");

    return 0;
}