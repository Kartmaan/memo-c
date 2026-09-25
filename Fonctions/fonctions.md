# Les Fonctions en Langage C

En programmation, une **fonction** est un bloc de code autonome conçu pour accomplir une tâche précise.

Plutôt que d'écrire un programme d'un seul tenant dans le `main`, découper son code en fonctions permet de **réutiliser du code** sans le dupliquer, de **faciliter la lecture** et de **simplifier le débogage**.

---

## 1. Structure d'une Fonction

En C, la définition d'une fonction comporte toujours trois éléments principaux : son **type de retour**, son **nom**, et ses **paramètres** entre parenthèses.

* **Type de retour :** Le type de donnée que la fonction renvoie à la fin de son exécution (`int`, `double`, `char`, `struct...`). Si la fonction ne renvoie rien, on utilise le type **`void`**.
* **Nom :** Le nom de la fonction, qui doit être unique dans le programme et respecter les règles de nommage des identificateurs.
* **Paramètres :** Les variables reçues par la fonction pour effectuer son travail (optionnels, écrire `void` entre parenthèses s'il n'y en a aucun).
* **`return` :** L'instruction qui renvoie le résultat et interrompt immédiatement l'exécution de la fonction.

```c
int additionner(int a, int b) { // Type de retour + Nom + Paramètres
    // Bloc d'instructions
    return a + b; // Retourne une valeur du type spécifié
}
```

---

## 2. Le Prototype (Déclaration) vs La Définition

Le compilateur C lit le fichier du haut vers le bas. Si tu appelles une fonction dans le `main` alors qu'elle est écrite plus bas dans le fichier, le compilateur génère un avertissement ou une erreur.

Pour organiser proprement son code, on utilise un **prototype** (déclaration) avant le `main`, puis la **définition** complète après.

```c
#include <stdio.h>

// 1. PROTOTYPE (Déclaration terminée par un point-virgule)
int multiplier(int a, int b);

int main(void) {
    // 2. APPEL DE LA FONCTION
    int res = multiplier(4, 5);
    printf("Résultat : %d\n", res);
    return 0;
}

// 3. DÉFINITION (Implémentation du code)
int multiplier(int a, int b) {
    return a * b;
}

```

> **En projet multifichier :** Les prototypes sont placés dans les fichiers d'en-tête (`.h`) et les définitions dans les fichiers sources (`.c`).

---

## 3. Le Mode de Passage des Arguments

C'est l'un des concepts les plus importants du langage C. Il existe deux façons de transmettre une donnée à une fonction :

### A. Passage par Valeur (Par défaut)

La fonction reçoit une **copie** de la variable. Toute modification effectuée sur le paramètre à l'intérieur de la fonction n'impacte pas la variable d'origine.

```c
void tenter_modifier(int x) {
    x = 99; // Ne modifie que la copie locale
}

int main(void) {
    int a = 10;
    tenter_modifier(a);
    // 'a' vaut toujours 10 !
    return 0;
}

```

### B. Passage par Adresse / Pointeur

En passant l'**adresse mémoire** d'une variable (`&a`) à un pointeur, la fonction peut directement lire et **modifier la variable d'origine**.

```c
void modifier_vrai(int *ptr) {
    *ptr = 99; // Modifie la valeur située à l'adresse pointée
}

int main(void) {
    int a = 10;
    modifier_vrai(&a);
    // 'a' vaut désormais 99 !
    return 0;
}

```

---

## 4. Portée des Variables (*Scope*)

* **Variables locales :** Déclarées à l'intérieur d'une fonction, elles n'existent que dans le bloc `{}` de cette fonction. Elles sont automatiquement détruites à la fin de l'exécution de la fonction (stockées sur la **Pile / Stack**).
* **Variables globales :** Déclarées en dehors de toute fonction. Accessibles partout, mais déconseillées car elles rendent le code dur à maintenir et vulnérable aux effets de bord.

---

## Récapitulatif

* **`void` :** S'utilise comme type de retour si la fonction ne renvoie rien, ou en paramètre `(void)` si elle ne prend aucun argument.
* **Prototype :** Déclaration de la fonction (`type nom(paramètres);`) nécessaire si la fonction est définie sous le `main` ou dans un fichier `.h`.
* **Copie vs Adresse :**
* Transmettre `x` passe une **copie** (lecture seule).
* Transmettre `&x` permet à la fonction de **modifier `x**` via un pointeur (`*ptr`).


* **Tableaux en paramètres :** Un tableau est toujours transmis par adresse. Il faut donc toujours lui associer un paramètre indiquant sa taille (ex: `void afficher(int tab[], int taille)`).