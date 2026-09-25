
---

# Les Structures en Langage C (`struct`)

Dans les bases du langage C, les variables simples (`int`, `float`, `char`) permettent de stocker une seule donnée. Les tableaux permettent d'en stocker plusieurs, mais à condition qu'elles soient toutes du **même type**.

Les **structures** (`struct`) permettent de franchir cette limite en créant de **nouveaux types de données sur mesure**, capables d'assembler plusieurs variables de **types différents** sous un même nom.

---

## 1. Pourquoi utiliser une structure ?

Imaginons que nous souhaitions représenter un livre dans un programme. Un livre est composé :

* d'un titre (`char[]`)
* d'un nombre de pages (`int`)
* d'un prix (`float`)

Sans structure, il faudrait gérer 3 variables indépendantes ou 3 tableaux parallèles.

Avec une structure, nous modélisons un objet logique unique :

```
             STRUCTURE "Livre"
+------------------------------------------+
|  .titre   : "Le Comte de Monte-Cristo"   | (char[100])
|  .pages   : 1200                         | (int)
|  .prix    : 24.90                        | (float)
+------------------------------------------+

```

---

## 2. Déclaration et Types Personnalisés (`typedef`)

### Déclaration de base (`struct`)

La déclaration d'une structure sert de **moule** (ou de patron). Elle ne réserve pas encore de mémoire en RAM.

```c
struct Livre {
    char titre[100];
    int pages;
    float prix;
};

```

Pour créer une variable avec cette structure, la syntaxe standard exige de répéter le mot-clé `struct` :

```c
struct Livre mon_livre; // Déclaration d'une variable 'mon_livre'

```

---

### Simplification avec `typedef`

Pour éviter de réécrire `struct` à chaque déclaration, on utilise `typedef` afin de créer un alias de type plus lisible.

```c
typedef struct {
    char titre[100];
    int pages;
    float prix;
} Livre; // 'Livre' devient le nom du nouveau type de donnée

```

Il devient alors possible de déclarer une variable aussi simplement qu'un `int` :

```c
Livre mon_livre; // Propre et concis !

```

---

## 3. Accès aux Champs : L'Opérateur Point `.`

Pour lire ou modifier un élément interne (appelé un **champ** ou une **membre**) d'une structure, on utilise l'opérateur **point (`.`)**.

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char titre[100];
    int pages;
    float prix;
} Livre;

int main(void) {
    // Initialisation directe lors de la déclaration
    Livre l1 = {"Fondation", 255, 8.50f};

    // Modification d'un champ
    l1.prix = 9.90f;

    // Lecture des champs
    printf("Titre : %s\n", l1.titre);
    printf("Pages : %d\n", l1.pages);
    printf("Prix  : %.2f €\n", l1.prix);

    return 0;
}

```

---

## 4. Structures et Pointeurs : L'Opérateur Flèche `->`

Lorsqu'on manipule une structure via un **pointeur** (notamment lors du passage à une fonction pour modifier la donnée d'origine sans faire de copie coûteuse), l'accès aux champs change.

On remplace l'opérateur point (`.`) par l'opérateur **flèche (`->`)**.

```c
#include <stdio.h>

typedef struct {
    char nom[50];
    int age;
} Personne;

// Fonction recevant l'ADRESSE de la structure via un pointeur
void feter_anniversaire(Personne *p) {
    // p->age est un raccourci syntaxique pour écriture (*p).age
    p->age++; 
}

int main(void) {
    Personne p1 = {"Alice", 20};

    // On passe l'adresse (&p1)
    feter_anniversaire(&p1);

    printf("%s a maintenant %d ans.\n", p1.nom, p1.age); // Affiche 21 ans
    return 0;
}

```

---

## 5. Tableaux de Structures

Comme n'importe quel autre type, les structures peuvent être regroupées au sein d'un tableau pour gérer des collections d'objets (ex: une bibliothèque de livres, une promo d'étudiants).

```c
Livre bibliotheque[100]; // Un tableau contenant 100 structures 'Livre'

// Accès au prix du 1er livre (indice 0)
bibliotheque[0].prix = 15.0f;

// Parcours du tableau
for (int i = 0; i < 3; i++) {
    printf("Livre %d : %s\n", i + 1, bibliotheque[i].titre);
}

```

---

## 📑 Récapitulatif

* **Rôle :** Assembler des variables de types différents sous un même nom logique.
* **`typedef` :** Permet d'éliminer le mot-clé `struct` devant chaque variable pour alléger l'écriture.
* **Opérateur `.` (Point) :** S'utilise sur une variable structure classique (`variable.champ`).
* **Opérateur `->` (Flèche) :** S'utilise sur un **pointeur** vers une structure (`pointeur->champ`).
* **Mémoire :** Passer une structure à une fonction se fait préférentiellement par **adresse** (`Personne *p`) afin d'éviter la duplication de toute la mémoire occupée par la structure.