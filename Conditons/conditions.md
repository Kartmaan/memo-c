# Les Conditions en Langage C

En programmation, les **structures conditionnelles** permettent à un programme de prendre des décisions et d'exécuter différents blocs de code en fonction de conditions vraies ou fausses.

En C, une condition est évaluée comme une valeur booléenne :

* **`0`** représente le **FAUX** (*False*).
* **Toute valeur différente de 0** (généralement `1`) représente le **VRAI** (*True*).

---

## 1. La Structure `if`, `else if`, `else`

### La règle d'enchaînement fondamentale

* **`if`** est l'élément déclencheur. Il peut exister seul.
* **`else if`** et **`else`** sont des compléments : ils ne peuvent **JAMAIS** exister seuls et doivent **obligatoirement faire suite à un `if**` (ou à un `else if` qui suit un `if`).

```
  [if (condition_1)]          <-- Obligatoire pour démarrer la chaîne
          │
  [else if (condition_2)]     <-- Optionnel (0, 1 ou plusieurs)
          │
  [else]                      <-- Optionnel (0 ou 1 seul à la fin)

```

---

## 2. Différence essentielle : `if` successifs vs `else if`

C'est un piège très fréquent chez les débutants. Comprendre la différence d'exécution entre plusieurs `if` indépendants et une chaîne `if ... else if` est capital.

### Cas A : Des `if` successifs (Évaluation de CHAQUE condition)

Le programme teste **toutes** les conditions les unes après les autres, indépendamment des résultats précédents.

```c
int age = 17;

if (age >= 10) {
    printf("Vous avez au moins 10 ans.\n"); //  VRAI -> S'exécute !
}
if (age >= 16) {
    printf("Vous avez au moins 16 ans.\n"); //  VRAI -> S'exécute AUSSI !
}
if (age >= 18) {
    printf("Vous etes majeur.\n");           // ❌ FAUX -> Ignoré
}
// Résultat : Les deux premiers messages s'affichent !

```

---

### Cas B : Chaîne `if` / `else if` (Évaluation EXCLUSIVE)

Dès qu'une condition est **VRAIE**, le bloc correspondant est exécuté et **tout le reste de la chaîne (`else if` et `else`) est immédiatement ignoré**, même si les conditions suivantes auraient pu être vraies.

```c
int age = 17;

if (age >= 10) {
    printf("Vous avez au moins 10 ans.\n"); //  VRAI -> S'exécute !
}
else if (age >= 16) {
    printf("Vous avez au moins 16 ans.\n"); // ⏩ Ignoré ! (Le 'if' précédent a déjà réussi)
}
else if (age >= 18) {
    printf("Vous etes majeur.\n");           // ⏩ Ignoré !
}
// Résultat : Seul le premier message s'affiche !

```

---

### Exemple Parlant : Attribuer une mention à un examen

Pour attribuer une mention, les plages de notes s'excluent mutuellement. C'est le cas d'usage typique du `else if` :

```c
#include <stdio.h>

int main(void) {
    float note = 15.5f;

    if (note < 10.0f) {
        printf("Ajourne\n");
    } 
    else if (note < 12.0f) { // Évalué SEULEMENT SI note >= 10.0f
        printf("Passable\n");
    } 
    else if (note < 14.0f) { // Évalué SEULEMENT SI note >= 12.0f
        printf("Mention Assez Bien\n");
    } 
    else if (note < 16.0f) { // Évalué SEULEMENT SI note >= 14.0f
        printf("Mention Bien\n"); //  S'exécute pour 15.5
    } 
    else {                   // S'exécute si AUCUNE des conditions précédentes n'est vraie (note >= 16.0f)
        printf("Mention Tres Bien\n");
    }

    return 0;
}

```

---

## 3. L'Instruction `switch` (Sélection multiple)

Lorsque l'on doit comparer **une seule variable entière ou un caractère (`char`)** à plusieurs valeurs exactes, `switch` est plus lisible qu'une succession de `if ... else if`.

```c
#include <stdio.h>

int main(void) {
    char choix = 'B';

    switch (choix) {
        case 'A':
            printf("Option A choisie.\n");
            break; // OBLIGATOIRE pour sortir du switch !
        case 'B':
            printf("Option B choisie.\n");
            break;
        case 'C':
            printf("Option C choisie.\n");
            break;
        default: // Équivalent du 'else' (si aucun cas ne correspond)
            printf("Choix invalide.\n");
            break;
    }

    return 0;
}

```

> ⚠️ **Attention à l'oubli du `break` :** Sans le mot-clé `break;`, l'exécution continue ("cascade") dans les blocs `case` suivants, même si leurs valeurs ne correspondent pas.

---

## 4. Les Opérateurs Logiques et l'Opérateur Ternaire

### Opérateurs de comparaison

* `==` (Égal à) — *Attention à ne pas confondre avec l'affectation `=` !*
* `!=` (Différent de)
* `>`, `<`, `>=`, `<=`

### Opérateurs logiques

* **`&&` (ET)** : Vrai si **toutes** les conditions sont vraies (`cond1 && cond2`).
* **`||` (OU)** : Vrai si **au moins une** condition est vraie (`cond1 || cond2`).
* **`!` (NON)** : Inverse le résultat logique (`!vrai` devient `faux`).

### L'Opérateur Ternaire (Raccourci conditionnel)

Permet d'écrire une condition simple sur une seule ligne.

*Syntaxe :* `(condition) ? valeur_si_vrai : valeur_si_faux;`

```c
int a = 10, b = 20;
// Stocke le maximum entre a et b
int max = (a > b) ? a : b; // max vaudra 20

```

---

## Récapitulatif

* **Ordre strict :** `else if` et `else` sont indissociables d'un `if` préalable.
* **`if` successifs :** Le programme évalue **chaque** condition.
* **`if ... else if` :** Le programme s'arrête à la **première** condition vraie et ignore la suite.
* **`switch` :** Idéal pour tester des valeurs entières/caractères exactes (ne pas oublier `break`).
* **Piège `=` vs `==` :** `if (x = 5)` affecte 5 à `x` (toujours vrai !), alors que `if (x == 5)` teste l'égalité.