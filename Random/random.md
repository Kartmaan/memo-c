
---

# L'Aléatoire en Informatique et en Langage C

L'un des plus grands paradoxes de l'informatique réside dans la génération du hasard : **un ordinateur est une machine purement déterministe**. Soumis à un même état initial et aux mêmes instructions, un processeur produira systématiquement le même résultat.

Alors, comment générer du hasard en programmation ?

---

## 1. Vrai Aléatoire (TRNG) vs Pseudo-Aléatoire (PRNG)

Pour contourner ce déterminisme, l'informatique distingue deux grandes catégories de générateurs :

### A. Le Vrai Aléatoire (*True Random Number Generator - TRNG*)

Les générateurs physiques mesurent des **phénomènes imprévisibles du monde réel** :

* Le bruit thermique de la carte mère ou les fluctuations électriques.
* Les délais d'interruption du clavier ou les mouvements de la souris.
* La désintégration radioactive ou des capteurs de bruit atmosphérique.

> **Cas d'usage :** Indispensable pour la **cryptographie**, la génération de clés de chiffrement et la sécurité informatique.

### B. Le Pseudo-Aléatoire (*Pseudo-Random Number Generator - PRNG*)

Les générateurs logiciels appliquent une **formule mathématique** pour produire une suite de nombres qui *semble* aléatoire.

* Si l'on ne connaît pas la formule, la suite paraît chaotique.
* Si l'on connaît la valeur de départ (appelée la **graine** ou **seed**), la suite devient $100\%$ prévisible.

> **Cas d'usage :** Jeux vidéo, simulations scientifiques, algorithmes de tri ou d'apprentissage, et code d'apprentissage en C. Par exemple le jeu vidéo Minecraft utilise un PRNG pour générer ses mondes : la seed de départ est un entier de 32 bits, et le monde généré est **identique** pour une même seed.

---

## 2. Le Fonctionnement de `rand()` et le Générateur Congruentiel Linéaire

En langage C, la fonction `rand()` (issue de la bibliothèque `<stdlib.h>`) repose historiquement sur un algorithme simple : le **Générateur Congruentiel Linéaire** (LCG).

### La formule mathématique

Chaque nombre suivant ($X_{n+1}$) est calculé à partir du nombre précédent ($X_n$) selon la formule :

$$X_{n+1} = (a \cdot X_n + c) \pmod m$$

* $X_0$ : La **graine** initiale (`srand`).
* $a$ : Le multiplicateur.
* $c$ : L'incrément.
* $m$ : Le modulo (qui définit la limite supérieure des valeurs).

### Pourquoi l'initialisation avec `time(NULL)` est indispensable ?

Si tu n'initialises pas la graine avec `srand()`, le compilateur utilise par défaut $X_0 = 1$. L'algorithme appliquera exactement les mêmes calculs à chaque lancement, produisant **toujours la même séquence de nombres**.

En fournissant `time(NULL)` (le nombre de secondes écoulées depuis le 1er janvier 1970) à `srand()`, la valeur initiale $X_0$ change à chaque seconde, donnant l'illusion d'un tirage nouveau à chaque exécution.

---

## 3. Pourquoi `rand()` limite souvent sa plage à $32\ 767$ (`RAND_MAX`) ?

Sur plusieurs environnements (notamment sous Windows avec Visual Studio ou MinGW), la constante `RAND_MAX` vaut **$32\ 767$** ($2^{15} - 1$).

Cette contrainte s'explique par trois facteurs historiques et techniques :

```
                  16 BITS SIGNÉ (Historique)
 +---+-------------------------------------------------+
 | S | 15 bits de données (Valeurs : 0 à 32 767)       |
 +---+-------------------------------------------------+
   ^
 Bit de signe (0 = positif)

```

1. **L'héritage de l'architecture 16 bits :**
Au moment de la création du langage C et des systèmes comme MS-DOS, le type entier classique (`int`) était codé sur **16 bits** (2 octets). Un `int` signé 16 bits peut stocker des valeurs allant de $-32\ 768$ à $+32\ 767$. Comme `rand()` ne doit retourner que des valeurs positives ou nulles, sa limite maximale naturelle était fixée à $32\ 767$.
2. **La norme ISO C :**
La norme C exige uniquement que la constante `RAND_MAX` soit d'au moins $32\ 767$. Elle laisse les concepteurs de compilateurs libres de conserver cette limite ou d'en utiliser une plus grande.
3. **Compatibilité ascendante :**
Même si les processeurs modernes travaillent en 32 bits ou 64 bits (où un `int` fait 32 bits et permet d'atteindre $2\ 147\ 483\ 647$), certains compilateurs (notamment l'API Windows C Runtime) ont conservé `RAND_MAX = 32767` pour ne pas risquer de casser la compatibilité avec de vieux logiciels. À l'inverse, sous Linux/GCC, `RAND_MAX` a été étendu à $2\ 147\ 483\ 647$ ($2^{31} - 1$).

---

## 4. Comment franchir la limite de $32\ 767$ sans bibliothèque tiers ?

Pour générer un nombre sur une plage plus large (par exemple entre $0$ et $100\ 000$) sur un système où `RAND_MAX` vaut $32\ 767$, on combine deux appels à `rand()` pour créer un nombre de $30$ bits :

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Génère un nombre aléatoire entre 0 et max_exclus (ex: 100 000)
unsigned int grand_rand(unsigned int max_exclus) {
    // Combiner deux tirages 15-bits décalés pour former une valeur 30-bits (jusqu'à ~1 milliard)
    unsigned int grand_nombre = ((unsigned int)rand() << 15) | (unsigned int)rand();
    
    return grand_nombre % max_exclus;
}

int main(void) {
    srand((unsigned int)time(NULL));

    printf("Tirage grand format : %u\n", grand_rand(100000));
    return 0;
}

```

---

## Récapitulatif

* **PRNG vs TRNG :** `rand()` est un générateur **pseudo-aléatoire** (déterministe et calculé par une formule mathématique).
* **Initialisation :** N'appeler `srand(time(NULL))` qu'**une seule fois** en début de programme.
* **`RAND_MAX` :** Garantit au minimum $32\ 767$ selon la norme, héritage du codage des entiers sur 16 bits.
* **Formule usuelle d'intervalle $[A, B]$ :**
```c
int valeur = A + rand() % (B - A + 1);

```