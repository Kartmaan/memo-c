#include <stdio.h>
#include <string.h>

/*  
 ============================================================================
                            STRUCTURES EN C
 ============================================================================
Une structure est un type de données défini par l'utilisateur qui permet de 
regrouper plusieurs variables de types différents sous un même nom. C'est une 
manière d'organiser les données de manière plus logique et cohérente, surtout 
lorsqu'elles sont liées entre elles.

Exemple : On peut définir une structure pour représenter un étudiant, avec son 
nom, son âge et sa moyenne. Cela permet de manipuler toutes ces informations 
comme une seule entité, plutôt que de gérer chaque variable séparément.
*/

// ----------------------------------------------------
// 1. DÉCLARATION D'UNE STRUCTURE ET UTILISATION DE typedef
// ----------------------------------------------------

// Sans typedef : il faudrait écrire "struct Etudiant" à chaque déclaration de variable.
// Avec typedef : on crée un alias "Etudiant" plus court et lisible.
typedef struct {
    char nom[50];
    int age;
    float moyenne;
} Etudiant;

// ----------------------------------------------------
// 2. PROTOTYPES DE FONCTIONS
// ----------------------------------------------------
// Passage par valeur (lecture seule)
void afficher_etudiant(Etudiant e);

// Passage par adresse via pointeur (modification ou performance)
void anniversaire(Etudiant *e);

int main(void) {
    // ----------------------------------------------------
    // 3. INITIALISATION D'UNE STRUCTURE
    // ----------------------------------------------------
    printf("=== 1. INITIALISATION ET ACCÈS (Opérateur .) ===\n");

    // Déclaration et initialisation directe
    Etudiant e1 = {"Alice", 20, 15.5f};

    // Déclaration puis affectation champ par champ
    Etudiant e2;
    // Pour une chaîne de caractères, on utilise strcpy !
    strcpy(e2.nom, "Bob");
    e2.age = 22;
    e2.moyenne = 12.0f;

    // Affichage via la fonction
    afficher_etudiant(e1);
    afficher_etudiant(e2);

    // ----------------------------------------------------
    // 4. POINTEUR SUR STRUCTURE ET OPÉRATEUR FLÈCHE (->)
    // ----------------------------------------------------
    printf("\n=== 2. MODIFICATION VIA POINTEUR (Opérateur ->) ===\n");

    printf("Age de %s avant anniversaire : %d ans\n", e1.nom, e1.age);

    // On passe l'adresse de e1 (&e1) pour modifier la structure d'origine
    anniversaire(&e1);

    printf("Age de %s après anniversaire : %d ans\n", e1.nom, e1.age);

    // ----------------------------------------------------
    // 5. TABLEAU DE STRUCTURES
    // ----------------------------------------------------
    printf("\n=== 3. TABLEAU DE STRUCTURES ===\n");

    Etudiant promo[2] = {
        {"Charlie", 19, 14.0f},
        {"Diane", 21, 16.8f}
    };

    for (int i = 0; i < 2; i++) {
        printf("Élève n°%d : %s (Moyenne : %.2f/20)\n", i + 1, promo[i].nom, promo[i].moyenne);
    }

    return 0;
}

// ----------------------------------------------------
// DÉFINITION DES FONCTIONS
// ----------------------------------------------------

// Reçoit une COPIE de la structure (lecture simple)
void afficher_etudiant(Etudiant e) {
    // L'accès aux champs d'une variable classique se fait avec le POINT '.'
    printf("Étudiant : %s | Âge : %d ans | Moyenne : %.2f/20\n", e.nom, e.age, e.moyenne);
}

// Reçoit l'ADRESSE de la structure via un pointeur
void anniversaire(Etudiant *e) {
    // L'accès aux champs depuis un pointeur se fait avec la FLÈCHE '->'
    // 'e->age' est un raccourci pour écriture équivalente '(*e).age'
    e->age++;
}