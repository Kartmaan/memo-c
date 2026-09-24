
---

# Les Tableaux en Langage C

Un **tableau** (*array*) est une structure de données qui permet de stocker **plusieurs éléments de même type** sous un seul nom de variable, à des emplacements contigus (qui se suivent) en mémoire.

---

## 1. Pourquoi utiliser un tableau ?

Sans tableau, pour stocker les notes de 5 étudiants, il faudrait créer 5 variables distinctes :

```c
int note1 = 12, note2 = 15, note3 = 8, note4 = 19, note5 = 14;

```

Cette méthode devient vite ingérable s'il y a 100 ou 1000 notes. Avec un tableau, une seule ligne suffit :

```c
int notes[5] = {12, 15, 8, 19, 14};

```

---

## 2. Déclaration et Initialisation

### Déclaration

Pour déclarer un tableau, on indique le **type** des éléments, le **nom** du tableau et sa **taille** fixe entre crochets `[]` :

```c
type nom_du_tableau[taille];

```

*Exemples :*

```c
int scores[10];      // Un tableau de 10 entiers (contenu indéterminé au départ)
float prix[5];       // Un tableau de 5 nombres à virgule
char lettres[26];    // Un tableau de 26 caractères

```

### Initialisation

On peut remplir le tableau dès sa déclaration en utilisant des accolades `{}` :

```c
int notes[5] = {12, 15, 8, 19, 14}; // Tableau de 5 entiers rempli

// Astuce : Initialiser TOUS les éléments à zéro
int valeurs[100] = {0}; // Les 100 cases vaudront 0

```

---

## 3. Accès aux éléments : La règle du premier indice `0`

En C, **les indices d'un tableau commencent toujours à 0**.

Pour un tableau de taille $N$, les indices valides vont de `0` à $N - 1$.

```
Index :      [0]   [1]   [2]   [3]   [4]
          +-----+-----+-----+-----+-----+
Contenu : |  12 |  15 |   8 |  19 |  14 |
          +-----+-----+-----+-----+-----+

```

### Lire ou modifier une case

On accède à une case spécifique avec le nom du tableau suivi de l'indice entre crochets :

```c
int premiere_note = notes[0]; // Lit la valeur 12
notes[2] = 10;                 // Remplace la valeur 8 par 10

```

> ⚠️ **Piège classique (Dépassement de mémoire / Out of bounds) :**
> Si un tableau fait 5 cases, accéder à `notes[5]` est une erreur grave. C tente de lire une zone mémoire arbitraire qui ne lui appartient pas, ce qui peut provoquer un comportement imprévisible ou un crash (*Segmentation Fault*).

---

## 4. Parcourir un tableau avec une boucle `for`

La méthode standard pour traiter tous les éléments d'un tableau consiste à utiliser une boucle `for` avec une variable d'indice (`i`) variant de `0` à `taille - 1`.

```c
#include <stdio.h>

int main(void) {
    int notes[5] = {12, 15, 10, 19, 14};

    // Parcourir et afficher le tableau
    for (int i = 0; i < 5; i++) {
        printf("Note a l'indice [%d] = %d\n", i, notes[i]);
    }

    return 0;
}

```

---

## 5. Tableaux à deux dimensions (Matrices)

Un tableau à deux dimensions peut être imaginé comme une grille avec des **lignes** et des **colonnes**.

```c
// Syntaxe : type nom[lignes][colonnes];
int grille[2][3] = {
    {1, 2, 3},  // Ligne 0
    {4, 5, 6}   // Ligne 1
};

```

Pour parcourir une matrice, on utilise deux boucles `for` imbriquées :

```c
for (int l = 0; l < 2; l++) {        // Boucle sur les lignes
    for (int c = 0; c < 3; c++) {    // Boucle sur les colonnes
        printf("%d ", grille[l][c]);
    }
    printf("\n");
}

```

---

## 6. Passer un tableau à une fonction

En C, lorsqu'on passe un tableau à une fonction, le langage transmet en réalité l'**adresse mémoire** du premier élément (un pointeur).

Comme le tableau perd la notion de sa propre taille au sein de la fonction, il est **obligatoire de passer la taille du tableau en paramètre séparé**.

```c
#include <stdio.h>

// Prototype : tab[] indique un tableau, taille précise le nombre d'éléments
void afficher_tableau(int tab[], int taille) {
    for (int i = 0; i < taille; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

int main(void) {
    int mes_scores[4] = {100, 250, 400, 500};
    
    // Appel de la fonction
    afficher_tableau(mes_scores, 4);

    return 0;
}

```

---

## 📑 Récapitulatif pour la fiche mémo

* **Type unique :** Tous les éléments d'un tableau doivent obligatoirement être du même type (`int`, `float`, `char`...).
* **Taille fixe :** La taille d'un tableau statique est définie à la création et ne peut plus être modifiée pendant l'exécution (pour une taille variable, utiliser l'allocation dynamique avec `malloc`).
* **Indices :** De `0` à `N - 1`.
* **Fonctions :** Un tableau transmis à une fonction s'accompagne **toujours** de sa taille.