#include <stdio.h>
#include <stdbool.h> // Nécessaire pour utiliser le type booléen (bool)

int main(void) {
    // ----------------------------------------------------
    // 1. DÉCLARATION ET INITIALISATION DES TYPES DE BASE
    // ----------------------------------------------------

    // Entier (ex: -2147483648 à 2147483647 sur 32/64 bits)
    int age = 25;

    // Nombre à virgule flottante (précision simple ~6-7 décimales)
    float taille = 1.75f;

    // Nombre à virgule flottante (double précision ~15-17 décimales)
    double constante_pi = 3.1415926535;

    // Caractère unique (se déclare entre simple quote '')
    char initiale = 'A';

    // Booléen (true / false - requiert <stdbool.h>)
    bool est_actif = true;

    // ----------------------------------------------------
    // 2. VARIANTES DE TAILLE ET DE SIGNE
    // ----------------------------------------------------

    // Entier court (prend moins de mémoire, généralement 16 bits)
    short int annee = 2026;

    // Entier long (pour les très grands nombres)
    long long int population_mondiale = 8000000000LL;

    // Non signé (uniquement positif, permet d'étendre la valeur max positive, 2 fois celle d'un int signé)
    unsigned int score = 1500;

    // ----------------------------------------------------
    // 3. AFFICHAGE DES VARIABLES (Format Spécificateurs)
    // ----------------------------------------------------

    printf("--- TYPES DE BASE ---\n");
    printf("Âge : %d ans\n", age);                        // %d pour int
    printf("Taille : %.2f m\n", taille);                   // %.2f pour afficher 2 décimales
    printf("Pi : %.10lf\n", constante_pi);                 // %lf pour double
    printf("Initiale : %c\n", initiale);                   // %c pour char
    printf("Statut actif : %d\n\n", est_actif);            // 1 pour true, 0 pour false

    printf("--- VARIANTES ---\n");
    printf("Année : %hd\n", annee);                        // %hd pour short int
    printf("Population : %lld\n", population_mondiale);    // %lld pour long long int
    printf("Score : %u\n", score);                         // %u pour unsigned int

    return 0;
}