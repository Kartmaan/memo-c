# Les Énumérations en Langage C (`enum`)

En programmation, il est fréquent de devoir manipuler une variable qui ne peut prendre qu'un **nombre restreint de valeurs prédéfinies** (par exemple : les jours de la semaine, les directions d'une boussole ou l'état d'un jeu vidéo).

Plutôt que d'utiliser des chiffres arbitraires (comme `0`, `1`, `2`) peu lisibles, ou des chaînes de caractères ("Nord", "Sud") lourdes en mémoire, le langage C propose les **énumérations** (`enum`).

---

## 1. Pourquoi utiliser une énumération ?

Imaginons la gestion de l'état d'un joueur dans un jeu vidéo :

```c
// ❌ Mauvaise pratique : "Nombres magiques" sans signification explicite
int etat_joueur = 2; // Que signifie 2 ? En vie ? Mort ? En pause ?

```

Pour rendre le code explicite, on pourrait utiliser des constantes `#define`, mais cela n'associe aucun type strict à notre variable. L'énumération résout ce problème en **créant un nouveau type** associé à un ensemble de constantes textuelles :

```c
//  Bonne pratique : Code clair et auto-documenté
EtatJoueur etat_joueur = PAUSE;

```

---

## 2. Déclaration et Types Personnalisés (`typedef`)

### Déclaration de base (`enum`)

Une énumération définit une liste de mots-clés associés automatiquement à des **valeurs entières** (`int`).

```c
enum Jour {
    LUNDI,    // vaut 0 par défaut
    MARDI,    // vaut 1
    MERCREDI, // vaut 2
    JEUDI,    // vaut 3
    VENDREDI, // vaut 4
    SAMEDI,   // vaut 5
    DIMANCHE  // vaut 6
};

```

### Simplification avec `typedef`

Comme pour les structures, on associe presque toujours `typedef` à un `enum` pour s'affranchir du mot-clé `enum` lors des déclarations :

```c
typedef enum {
    LUNDI,
    MARDI,
    MERCREDI,
    JEUDI,
    VENDREDI,
    SAMEDI,
    DIMANCHE
} Jour;

// Utilisation directe du nouveau type :
Jour aujourdhui = LUNDI;

```

---

## 3. Fonctionnement Interne et Valeurs Personnalisées

Sous le capot, l'ordinateur traite une énumération comme un simple **entier (`int`)**.

### Attribution automatique

Par défaut, le premier élément vaut `0`, et chaque élément suivant prend la valeur du précédent $+ 1$.

### Attribution explicite

Il est possible de forcer des valeurs numériques spécifiques :

```c
typedef enum {
    CODE_OK = 200,
    CODE_NON_TROUVE = 404,
    CODE_ERREUR_SERVEUR = 500
} CodeStatut;

```

Si une valeur n'est pas précisée, elle prend la valeur de la précédente $+ 1$ :

```c
typedef enum {
    NORD = 1, // Vaut 1
    EST,      // Vaut 2
    SUD,      // Vaut 3
    OUEST     // Vaut 4
} Direction;

```

---

## 4. Cas d'Usage Principal : L'Instruction `switch`

Les énumérations se combinent idéalement avec l'instruction `switch` pour traiter distinctement chaque état d'un programme :

```c
#include <stdio.h>

typedef enum {
    ARRET,
    EN_COURS,
    PAUSE
} EtatJeu;

int main(void) {
    EtatJeu etat = PAUSE;

    switch (etat) {
        case ARRET:
            printf("Le jeu est ferme.\n");
            break;
        case EN_COURS:
            printf("Partie en cours...\n");
            break;
        case PAUSE:
            printf("Jeu en pause.\n");
            break;
    }

    return 0;
}

```

---

## 5. Piège Classique : Affichage et Saisie

Comme une énumération est stockée sous forme d'entier, passer une variable `enum` à `printf` avec `%d` affichera **sa valeur numérique**, et non son nom en toutes lettres.

```c
Jour j = MARDI;
printf("%d\n", j); // Affiche '1' et NON PAS "MARDI"

```

Pour afficher une chaîne de caractères correspondant à un `enum`, on utilise généralement un tableau de chaînes ou un `switch` dédié :

```c
const char *noms_jours[] = {
    "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"
};

printf("Aujourd'hui : %s\n", noms_jours[j]); // Affiche "Aujourd'hui : Mardi"

```

---

## 📑 Récapitulatif pour la fiche mémo

* **Rôle :** Associer des noms lisibles à un ensemble restreint de valeurs entières (`int`).
* **Lisibilité :** Élimine les "chiffres magiques" et clarifie l'intention du code.
* **Valeurs :** Commence à `0` par défaut, incrementé de $+1$ à chaque constante.
* **`typedef` :** Permet de créer un alias propre (ex: `typedef enum { ... } MonEnum;`).
* **Stockage :** Traité comme un entier (`int`) en mémoire par le compilateur.