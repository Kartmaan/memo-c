/*  
 ============================================================================
                        ALLOCATION DYNAMIQUE EN C
 ============================================================================
L'allocation dynamique permet de réserver de la mémoire à l'exécution, 
contrairement à l'allocation statique qui se fait à la compilation.
Elle est particulièrement utile lorsque la taille des données n'est pas connue 
à l'avance ou peut varier.

Lorsqu'on déclare un tableau de la sorte : `int tableau[10];`, la taille est fixe 
et connue à la compilation (impossible de modifier la taille à l'exécution). 
En revanche, avec l'allocation dynamique, on peut demander à l'utilisateur 
combien d'éléments il souhaite stocker, et allouer la mémoire en conséquence.
Car il est parfois impossible de savoir à l'avance combien d'éléments seront 
nécessaires, surtout dans des programmes interactifs ou des applications 
qui traitent des données externes.
*/

#include <stdio.h>
#include <stdlib.h> // Indispensable pour malloc, calloc, realloc et free

int main(void) {
    // ----------------------------------------------------
    // ALLOCATION AVEC malloc()
    // ----------------------------------------------------
    printf("=== 1. ALLOCATION D'UN TABLEAU DYNAMIQUE (malloc) ===\n");

    int taille = 0;
    printf("Combien d'elements souhaitez-vous stocker ? ");
    // Pour l'exemple, supposons que l'utilisateur veut 5 éléments
    taille = 5; 
    printf("%d\n", taille);

    /*
    *tableau contient l'adresse du premier élément du bloc de mémoire alloué dynamiquement.
    C'est un pointeur vers un entier (int*), et il peut être utilisé comme un tableau, 
    ce qui permet d'accéder aux éléments du bloc de mémoire en utilisant un index.
    
    La mémoire est réservée sur le tas (heap) et non sur la pile (stack), ce qui permet 
    de gérer des tailles de données plus importantes et dynamiques. 

    malloc n'initialise pas la mémoire, donc les valeurs contenues dans le tableau sont 
    indéterminées jusqu'à ce qu'elles soient explicitement définies. Contrairement, 
    calloc initialise la mémoire à zéro.
    */
    int *tableau = malloc(taille * sizeof(int)); // calcul la taille totale en octets

    // TEST DE SÉCURITÉ OBLIGATOIRE : Toujours vérifier si malloc a réussi !
    if (tableau == NULL) {
        fprintf(stderr, "Erreur : Allocation memoire echouee !\n");
        return 1; // On quitte le programme avec un code d'erreur
    }

    // Remplissage et affichage du tableau
    for (int i = 0; i < taille; i++) {
        tableau[i] = (i + 1) * 10; // Accès identique à un tableau classique
        printf("tableau[%d] = %d\n", i, tableau[i]);
    }

    // ----------------------------------------------------
    // REDIMENSIONNEMENT AVEC realloc()
    // ----------------------------------------------------
    printf("\n=== 2. REDIMENSIONNEMENT (realloc) ===\n");

    int nouvelle_taille = 8;
    printf("Agrandissement du tableau a %d elements...\n", nouvelle_taille);

    // realloc prend l'ancien pointeur et la nouvelle taille totale en octets
    int *tmp = realloc(tableau, nouvelle_taille * sizeof(int));

    if (tmp == NULL) {
        fprintf(stderr, "Erreur : Impossible de redimensionner !\n");
        free(tableau); // On libère l'ancienne mémoire avant de quitter
        return 1;
    }
    tableau = tmp; // On met à jour notre pointeur principal

    // Initialisation des nouveaux éléments ajoutés (indices 5 à 7)
    for (int i = taille; i < nouvelle_taille; i++) {
        tableau[i] = (i + 1) * 10;
    }

    // Affichage complet
    for (int i = 0; i < nouvelle_taille; i++) {
        printf("tableau[%d] = %d\n", i, tableau[i]);
    }

    // ----------------------------------------------------
    // LIBÉRATION DE LA MÉMOIRE (free)
    // ----------------------------------------------------
    printf("\n=== 3. LIBERATION DE LA MEMOIRE (free) ===\n");

    // On rend la mémoire au système d'exploitation
    free(tableau);

    // Bonnes pratiques : Mettre le pointeur à NULL pour éviter de l'utiliser par erreur
    tableau = NULL; 

    printf("Memoire liberee avec succes.\n");

    return 0;
}