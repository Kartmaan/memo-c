/*
 ============================================================================
                      L'ALLOCATION DYNAMIQUE EN C
 ============================================================================
 
 1. QU'EST-CE QUE C'EST ?
    Jusqu'à présent, la mémoire de vos variables et tableaux était allouée 
    de manière STATIQUE sur la "Pile" (Stack). Sa taille devait être connue 
    dès la compilation (ex: int tab[100];).
    
    L'allocation dynamique permet de demander au système d'exploitation de la 
    mémoire sur le "Tas" (Heap) PENDANT l'exécution du programme, selon les 
    besoins réels (ex: un tableau dont la taille est choisie par l'utilisateur).
    (voir allocdyn.md pour plus de détails)

 2. LES FONCTIONS ESSENTIELLES (<stdlib.h>) :
    - malloc(taille_en_octets) : 
        RÉSERVE un bloc de mémoire non initialisé. Renvoie un pointeur vers 
        le premier octet, ou NULL en cas d'échec (mémoire saturée).
    - calloc(nombre, taille_unitaire) : 
        RÉSERVE de la mémoire et la REMPLIT DE ZÉROS.
    - realloc(pointeur, nouvelle_taille) : 
        REDIMENSIONNE un bloc déjà alloué (agrandit ou rétrécit).
    - free(pointeur) : 
        LIBÈRE la mémoire allouée. C'est OBLIGATOIRE pour éviter les 
        fuites de mémoire (memory leaks).

 3. LA RÈGLE D'OR :
    "Tout malloc/calloc doit avoir son free !"
    Une fois la mémoire libérée avec free(), le pointeur ne doit plus 
    être utilisé (mettez-le à NULL par sécurité).
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h> // Indispensable pour malloc, calloc, realloc et free

int main(void) {
    // ----------------------------------------------------
    // 1. ALLOCATION AVEC malloc()
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
    // 2. REDIMENSIONNEMENT AVEC realloc()
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
    // 3. LIBÉRATION DE LA MÉMOIRE (free)
    // ----------------------------------------------------
    printf("\n=== 3. LIBERATION DE LA MEMOIRE (free) ===\n");

    // On rend la mémoire au système d'exploitation
    free(tableau);

    // Bonnes pratiques : Mettre le pointeur à NULL pour éviter de l'utiliser par erreur
    tableau = NULL; 

    printf("Memoire liberee avec succes.\n");

    return 0;
}