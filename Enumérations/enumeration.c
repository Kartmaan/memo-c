#include <stdio.h>

/*  
 ============================================================================
                            ENUMERATION EN C
 ============================================================================
Une énumération est un type de données défini par l'utilisateur qui consiste 
en un ensemble de constantes entières nommées. Elle est utile pour représenter 
des ensembles de valeurs discrètes et pour améliorer la lisibilité du code.

Exemple : On peut définir une énumération pour représenter les jours de la 
semaine, les états d'un jeu, ou les codes de réponse HTTP.

En C, les énumérations sont déclarées avec le mot-clé `enum`. Chaque élément 
de l'énumération est associé à une valeur entière, par défaut commençant à 0 
et incrémentée de 1 pour chaque élément suivant. Il est également possible 
d'assigner des valeurs spécifiques à certains éléments.
*/

// ----------------------------------------------------
// DÉCLARATION ET UTILISATION DE typedef
// ----------------------------------------------------

// Sans typedef : il faudrait écrire "enum Jour" à chaque fois.
// Par défaut, le C attribue automatique des entiers à partir de 0 :
// LUNDI = 0, MARDI = 1, MERCREDI = 2, etc.
typedef enum {
    LUNDI,      // 0
    MARDI,      // 1
    MERCREDI,   // 2
    JEUDI,      // 3
    VENDREDI,   // 4
    SAMEDI,     // 5
    DIMANCHE    // 6
} Jour;

// On peut aussi imposer ses propres valeurs numériques :
typedef enum {
    CODE_OK = 200,
    CODE_NON_TROUVE = 404,
    CODE_ERREUR_SERVEUR = 500
} CodeReponse;

// ----------------------------------------------------
// UTILISATION AVEC UNE STRUCTURE ET UN SWITCH
// ----------------------------------------------------

typedef enum {
    ARRET,
    EN_COURS,
    PAUSE
} EtatJeu;

int main(void) {
    // ----------------------------------------------------
    // INITIALISATION ET AFFECTATION
    // ----------------------------------------------------
    printf("=== 1. UTILISATION SIMPLE ===\n");

    // Déclaration d'une variable de type énumération prenant la valeur MERCREDI
    Jour aujourdhui = MERCREDI;

    // En réalité, 'aujourdhui' stocke l'entier 2
    printf("Valeur numerique de MERCREDI : %d\n", aujourdhui);

    if (aujourdhui == SAMEDI || aujourdhui == DIMANCHE) {
        printf("C'est le week-end !\n");
    } else {
        printf("Au travail !\n\n");
    }

    // ----------------------------------------------------
    // L'ÉNUMÉRATION DANS UN SWITCH (Cas d'usage principal)
    // ----------------------------------------------------
    printf("=== 2. ÉTAT D'UN JEU (SWITCH) ===\n");

    EtatJeu etat = PAUSE;

    switch (etat) {
        case ARRET:
            printf("Le jeu est ferme.\n");
            break;
        case EN_COURS:
            printf("Partie en cours...\n");
            break;
        case PAUSE:
            printf("Jeu en pause. Appuyez sur ECHAP pour reprendre.\n");
            break;
    }

    // ----------------------------------------------------
    // ÉNUMÉRATION AVEC VALEURS PERSONNALISÉES
    // ----------------------------------------------------
    printf("\n=== 3. CODES ERREURS ===\n");

    CodeReponse retour = CODE_NON_TROUVE;
    printf("Code statut recu : %d\n", retour);

    return 0;
}