#include <stdio.h>
#include <string.h> // Nécessaire pour strlen, strcpy, strcat, strcmp, etc.

int main(void) {
    // ----------------------------------------------------
    // 1. DÉCLARATION ET CARACTÈRE DE FIN DE CHAÎNE (\0)
    // ----------------------------------------------------
    printf("=== 1. BASES DES CHAÎNES DE CARACTÈRES ===\n");

    // Une chaîne est un tableau de char se terminant par '\0' (null terminator)
    // C'est grâce à '\0' que les fonctions savent où s'arrête la chaîne en mémoire.
    char ch1[] = "Bonjour"; // Le compilateur réserve 8 octets (7 lettres + '\0')
    char ch2[20] = "Monde"; // Réserve 20 octets, la chaîne en utilise 6

    printf("Chaine 1 : %s\n", ch1);
    printf("Chaine 2 : %s\n\n", ch2);

    // ----------------------------------------------------
    // 2. LONGUEUR D'UNE CHAÎNE : strlen()
    // ----------------------------------------------------
    printf("=== 2. LONGUEUR (strlen) ===\n");

    // strlen() renvoie le nombre de caractères *sans* compter le '\0' final
    // sizet est un type entier non signé utilisé pour représenter la taille d'un objet en mémoire
    size_t longueur = strlen(ch1);
    printf("La longueur de \"%s\" est de %zu caracteres.\n", ch1, longueur);
    printf("La taille allouee en memoire (sizeof) est de %zu octets.\n\n", sizeof(ch1));

    // ----------------------------------------------------
    // 3. COPIE DE CHAÎNE : strcpy() ET strncpy()
    // ----------------------------------------------------
    printf("=== 3. COPIE (strcpy / strncpy) ===\n");

    char destination[30];

    // On ne peut PAS faire : destination = ch1; c'est interdit en C car destination est un tableau, pas un pointeur.
    // Il faut utiliser strcpy(destination, source)
    strcpy(destination, ch1);
    printf("Apres strcpy() : %s\n", destination);

    // Version sécurisée avec strncpy() : limite le nombre de caractères copiés. 
    // Cela évite les dépassements de tampon (buffer overflow).
    char destination_securisee[10];
    strncpy(destination_securisee, "TexteTresLong", sizeof(destination_securisee) - 1);
    destination_securisee[sizeof(destination_securisee) - 1] = '\0'; // Garantit le '\0' final
    printf("Apres strncpy() tronque : %s\n\n", destination_securisee);

    // ----------------------------------------------------
    // 4. CONCATÉNATION (FUSION) : strcat()
    // ----------------------------------------------------
    printf("=== 4. CONCATÉNATION (strcat) ===\n");

    char salutation[50] = "Hello ";
    strcat(salutation, "World !"); // Ajoute "World !" à la suite de "Hello "
    printf("Apres strcat() : %s\n\n", salutation);

    // ----------------------------------------------------
    // 5. COMPARAISON DE CHAÎNES : strcmp()
    // ----------------------------------------------------
    printf("=== 5. COMPARAISON (strcmp) ===\n");

    // On ne peut PAS comparer deux chaînes avec == (cela comparerait leurs adresses mémoires)
    // strcmp(a, b) renvoie :
    //   0  si les chaînes sont IDENTIQUES
    // < 0  si 'a' précède 'b' dans l'ordre alphabétique
    // > 0  si 'a' suit 'b' dans l'ordre alphabétique

    char mot1[] = "Code";
    char mot2[] = "Code";
    char mot3[] = "C";

    if (strcmp(mot1, mot2) == 0) {
        printf("\"%s\" et \"%s\" sont identiques.\n", mot1, mot2);
    }

    if (strcmp(mot1, mot3) != 0) {
        printf("\"%s\" et \"%s\" sont differents.\n", mot1, mot3);
    }

    return 0;
}