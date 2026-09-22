#include <stdio.h>
#include <stdlib.h>

// ----------------------------------------------------
// 1. UTILITÉ N°1 : MODIFIER UNE VARIABLE DEPUIS UNE FONCTION
// ----------------------------------------------------
// Sans pointeur (passage par valeur), 'nombre' serait copié et la
// variable d'origine ne changerait pas dans le main.
// Avec un pointeur 'int *ptr', on reçoit l'ADRESSE MÉMOIRE de la variable.
void doubler_valeur(int *ptr) {
    // L'opérateur '*' (déréférencement) permet d'accéder à la VALEUR
    // située à l'adresse stockée dans 'ptr'.
    *ptr = (*ptr) * 2; 
}

int main(void) {
    // ----------------------------------------------------
    // 2. DÉCLARATION, ADRESSE (&) ET DÉRÉFÉRENCEMENT (*)
    // ----------------------------------------------------
    printf("=== 1. BASES : VARIABLE VS POINTEUR ===\n");

    int age = 25; // Variable entière classique

    // Un pointeur est une variable qui contient l'ADRESSE MÉMOIRE d'une autre variable.
    // Le type du pointeur doit correspondre au type de la cible (int* pour un int).
    // On utilise l'opérateur '&' pour obtenir l'adresse d'une variable.
    int *p_age = &age; 

    printf("Valeur de 'age'                  : %d\n", age);
    printf("Adresse de 'age' dans la RAM (&)  : %p\n", (void*)&age);
    printf("Valeur contenue dans 'p_age'     : %p\n", (void*)p_age);
    printf("Valeur pointee par 'p_age' (*)   : %d\n\n", *p_age);

    // On peut modifier 'age' directement en passant par son pointeur :
    *p_age = 30; // "Va à l'adresse p_age et mets-y la valeur 30"
    printf("Nouvelle valeur de 'age' apres modification via le pointeur : %d\n\n", age);


    // ----------------------------------------------------
    // 3. UTILITÉ N°1 EN PRATIQUE : MODIFICATION EN FONCTION
    // ----------------------------------------------------
    printf("=== 2. PASSAGE PAR ADRESSE EN FONCTION ===\n");

    int compteur = 10;
    printf("Compteur avant fonction : %d\n", compteur);

    // On donne l'ADRESSE de compteur (&compteur) à la fonction
    doubler_valeur(&compteur);

    printf("Compteur apres doubler_valeur() : %d\n\n", compteur);


    // ----------------------------------------------------
    // 4. ARITHMÉTIQUE DES POINTEURS ET TABLEAUX
    // ----------------------------------------------------
    // En C, le nom d'un tableau est EN RÉALITÉ un pointeur vers son 1er élément.
    printf("=== 3. POINTEURS ET TABLEAUX ===\n");

    int notes[3] = {12, 15, 18};
    int *p_notes = notes; // Équivalent à &notes[0]

    // Accès classique vs Accès par arithmétique de pointeurs
    printf("Premier element (notes[0])     : %d\n", notes[0]);
    printf("Premier element (*p_notes)     : %d\n", *p_notes);

    // L'addition '+ 1' décale le pointeur vers la case mémoire suivante 
    // (le compilateur calcule automatiquement la taille d'un int en octets)
    printf("Deuxieme element (*(p_notes + 1)): %d\n", *(p_notes + 1));
    printf("Troisieme element (*(p_notes + 2)): %d\n\n", *(p_notes + 2));


    // ----------------------------------------------------
    // 5. BONNES PRATIQUES : LE POINTEUR NULL
    // ----------------------------------------------------
    printf("=== 4. SECURITE : POINTEUR NULL ===\n");

    // Quand un pointeur ne pointe sur rien, il faut TOUJOURS l'initialiser à NULL.
    // Tenter de déréférencer un pointeur non initialisé (sauvage) provoque un Segfault.
    int *p_securise = NULL;

    if (p_securise != NULL) {
        printf("Valeur : %d\n", *p_securise);
    } else {
        printf("Le pointeur est NULL, accès interdit en toute securite !\n");
    }

    return 0;
}