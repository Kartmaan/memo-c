#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int age = 20;
    bool a_permis = true;
    int note = 15;
    char choix_menu = 'B';

    // ----------------------------------------------------
    // 1. IF, ELSE IF, ELSE & OPÉRATEURS LOGIQUES
    // ----------------------------------------------------
    printf("=== 1. CONDITIONS SI / SINON ===\n");

    // && signifie ET (les deux conditions doivent être vraies)
    // || signifie OU (au moins une condition doit être vraie)
    // !  signifie NON (inverse l'état logique)
    if (age >= 18 && a_permis) {
        printf("Vous pouvez conduire une voiture.\n");
    } else if (age >= 18 && !a_permis) {
        printf("Vous êtes majeur mais vous n'avez pas le permis.\n");
    } else {
        printf("Vous êtes mineur, vous ne pouvez pas conduire.\n");
    }

    // ----------------------------------------------------
    // 2. COMPARAISONS ET ÉVALUATION MULTIPLE
    // ----------------------------------------------------
    printf("\n=== 2. ÉVALUATION D'UNE NOTE ===\n");

    if (note >= 16) {
        printf("Mention Très Bien\n");
    } else if (note >= 14) {
        printf("Mention Bien\n");
    } else if (note >= 10) {
        printf("Admis\n");
    } else {
        printf("Rattrapage ou Ajourné\n");
    }

    // ----------------------------------------------------
    // 3. L'OPÉRATEUR TERNAIRE (Condition condensée)
    // ----------------------------------------------------
    // Syntaxe : (condition) ? valeur_si_vrai : valeur_si_faux;
    printf("\n=== 3. OPÉRATEUR TERNAIRE ===\n");
    
    printf("Résultat : %s\n", (note >= 10) ? "Réussi" : "Échoué");

    // ----------------------------------------------------
    // 4. LA STRUCTURE SWITCH (Aiguillage sur une valeur)
    // ----------------------------------------------------
    // Idéal pour tester les égalités successives sur un entier ou un char.
    printf("\n=== 4. STRUCTURE SWITCH ===\n");

    switch (choix_menu) {
        case 'A':
            printf("Action : Démarrer la partie\n");
            break; // Le 'break' est OBLIGATOIRE pour sortir du switch
        case 'B':
            printf("Action : Charger une sauvegarde\n");
            break;
        case 'C':
            printf("Action : Quitter\n");
            break;
        default:
            printf("Option invalide !\n");
            break;
    }

    return 0;
}