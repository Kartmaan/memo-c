#include <stdio.h>

/*  
 ============================================================================
                        SPÉCIFICATEURS DE FORMAT EN C
 ============================================================================
Les spécificateurs de format sont utilisés dans les fonctions d'entrée/sortie 
(comme printf et scanf) pour indiquer le type de données à traiter.

Exemples de spécificateurs de format :
- %d : entier signé (int)
- %u : entier non signé (unsigned int)
- %f : nombre à virgule flottante (float)
- %lf : nombre à virgule flottante double précision (double)
- %c : caractère unique (char)
- %s : chaîne de caractères (char[])
- %p : adresse mémoire (void*)
*/

int main(void) {
    // ----------------------------------------------------
    // LES SPÉCIFICATEURS DE TYPE
    // ----------------------------------------------------
    int entier = -42;
    unsigned int entier_positif = 42000;
    float flottant = 3.14159f;
    double reel_double = 123456.7890123;
    char lettre = 'Z';
    char chaine[] = "Hello C";

    printf("=== 1. TYPES DE BASE ===\n");
    printf("%%d  (int signé)          : %d\n", entier);
    printf("%%u  (unsigned int)      : %u\n", entier_positif);
    printf("%%f  (float)             : %f\n", flottant);
    printf("%%lf (double)            : %lf\n", reel_double);
    printf("%%c  (char unique)       : %c\n", lettre);
    printf("%%s  (chaîne de caractères): %s\n", chaine);
    printf("%%p  (adresse mémoire)   : %p\n\n", (void*)&entier);

    // ----------------------------------------------------
    // LA DIFFÉRENCE ENTRE %d ET %i
    // ----------------------------------------------------
    // En sortie avec printf(), %d et %i font exactement la même chose.
    // La différence majeure réside lors de la saisie avec scanf() !
    
    int val_d, val_i;
    
    printf("=== 2. DIFFÉRENCE %%d vs %%i ===\n");
    printf("Avec printf : %%d = %d, %%i = %i (aucun changement)\n", entier, entier);
    
    // Exemple conceptuel pour scanf() :
    // Si l'utilisateur tape "012" :
    // - scanf("%d", &val_d) lira 12 (base 10).
    // - scanf("%i", &val_i) lira 10 (interprété comme de l'octal à cause du '0' initial).
    // Si l'utilisateur tape "0x12" :
    // - scanf("%i", &val_i) lira 18 (interprété comme de l'hexadécimal à cause du '0x').


    // ----------------------------------------------------
    // CONTRÔLE DE LA PRÉCISION ET DE LA LARGEUR
    // ----------------------------------------------------
    printf("\n=== 3. PRÉCISION ET ALIGNEMENT ===\n");
    
    // Arrondi / Nombre de décimales (%.Nf)
    printf("Flottant par défaut (%%f)   : %f\n", flottant);
    printf("Flottant 2 décimales (%%.2f) : %.2f\n", flottant);
    printf("Flottant 0 décimale  (%%.0f) : %.0f\n\n", flottant);

    // Largeur minimale et alignement (%Nm)
    printf("Largeur de 8 caractères, aligné à droite : [%8d]\n", 42);
    printf("Largeur de 8 caractères, aligné à gauche : [%-8d]\n", 42);
    printf("Remplissage avec des zéros (0N)         : [%08d]\n\n", 42);

    // ----------------------------------------------------
    // BASES NUMÉRIQUES (HEXADÉCIMAL ET OCTAL)
    // ----------------------------------------------------
    int valeur = 255;

    printf("=== 4. BASES NUMÉRIQUES ===\n");
    printf("Base 10 (%%d) : %d\n", valeur);
    printf("Base 16 (%%x) : %x  (minuscules)\n", valeur);
    printf("Base 16 (%%X) : %X  (majuscules)\n", valeur);
    printf("Base 8  (%%o) : %o\n", valeur);

    return 0;
}