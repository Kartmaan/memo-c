# Le Préprocesseur C : Directives, Macros et Gardes d'Inclusion

Avant même que le compilateur C (`gcc`) ne traduise le code source en langage machine, un premier outil entre en action : le **préprocesseur**.

Son rôle est d'effectuer des **traitements purement textuels** sur le code source (remplacement de texte, insertion de fichiers, suppression de blocs de code). Toutes les instructions destinées au préprocesseur commencent par le symbole **`#`** et ne se terminent **jamais par un point-virgule**.

```
Fichier .c  ──►  [ PRÉPROCESSEUR ]  ──►  Code nettoyé/étendu  ──►  [ COMPILATEUR ]  ──►  Objet (.o)

```

---

## 1. L'Inclusion de Fichiers : `#include`

La directive `#include` copie-colle littéralement le contenu d'un fichier d'en-tête (fichier `.h`) à l'endroit exact où se trouve la ligne.

### Chevrons `<>` vs Guillemets `""`

* **`#include <stdio.h>` (Chevrons) :**
Indique au préprocesseur de chercher le fichier dans les **dossiers système** du compilateur (ex: `/usr/include/`). Réservé aux bibliothèques standards du C ou bibliothèques tierces installées sur le système.
* **`#include "math_utils.h"` (Guillemets) :**
Indique au préprocesseur de chercher d'abord dans le **dossier courant** du projet local, puis dans les dossiers système si le fichier n'y est pas trouvé. Réservé à nos propres fichiers d'en-tête.

---

## 2. Les Macros et Constantes : `#define`

La directive `#define` permet d'associer un identifiant à un texte de remplacement. Le préprocesseur parcourt ensuite le code et effectue un **remplacement textuel brut**.

### A. Constantes de remplacement

Plutôt que d'utiliser des "nombres magiques" dans le code, on définit une constante symbolique (par convention en **MAJUSCULES**) :

```c
#define TAILLE_MAX 100
#define PI 3.141592

int tableau[TAILLE_MAX]; // Le préprocesseur remplacera par 'int tableau[100];'

```

### B. Macros avec paramètres

On peut créer de petites fonctions textuelles :

```c
#define CARRE(x) ((x) * (x))

```

> ⚠️ **Piège classique des parenthèses dans les macros :**
> Sans parenthèses autour de la variable `x` et de l'expression globale, des priorités d'opérateurs peuvent fausser les calculs.
> Par exemple, `CARRE(1 + 2)` s'étendra en `((1 + 2) * (1 + 2))` = $9$.
> Si la macro avait été écrite `#define CARRE(x) x * x`, l'extension aurait été `1 + 2 * 1 + 2` = $5$ !

---

## 3. Les Gardes d'Inclusion (*Include Guards*) : `#ifndef`, `#define`, `#endif`

Dans un projet multifichier, il arrive souvent que plusieurs fichiers `.c` ou `.h` incluent le même fichier d'en-tête (par exemple `structures.h`).

Sans protection, le préprocesseur va copier-coller plusieurs fois le contenu de ce fichier, ce qui génère une erreur de compilation pour **redéclaration de structures ou de types**.

### Le mécanisme des gardes d'inclusion

Pour éviter cela, **chaque fichier `.h` doit être enveloppé dans une garde d'inclusion** utilisant la compilation conditionnelle :

```c
// math_utils.h

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// --------------------------------------------------------
// Contenu du fichier .h (prototypes, typedef, struct)
// --------------------------------------------------------
int additionner(int a, int b);

#endif // MATH_UTILS_H

```

### Comment ça marche ?

1. **`#ifndef MATH_UTILS_H`** (*if not defined*) : Vérifie si le symbole `MATH_UTILS_H` a **déjà été défini**.
2. **Premier passage :** Le symbole n'existe pas. Le préprocesseur exécute `#define MATH_UTILS_H` (crée le symbole) puis lit tout le contenu du fichier jusqu'au `#endif`.
3. **Passages suivants :** Si un autre fichier ré-inclut `math_utils.h`, `#ifndef MATH_UTILS_H` renvoie **faux** (car le symbole existe désormais). Tout le contenu jusqu'au `#endif` est ignoré instantanément.

---

## 4. La Compilation Conditionnelle (`#ifdef`, `#else`, `#endif`)

Cette fonctionnalité permet d'inclure ou d'exclure du code lors de la compilation selon certaines conditions (par exemple pour gérer des modes de débogage ou du code multi-plateforme).

```c
#include <stdio.h>

// Décommenter pour activer les messages de debug
// #define DEBUG_MODE

int main(void) {
    int x = 42;

#ifdef DEBUG_MODE
    printf("[DEBUG] La valeur de x est : %d\n", x);
#endif

    printf("Execution normale du programme.\n");
    return 0;
}

```

---

## 📑 Récapitulatif

* **Préprocesseur :** Traitement de texte **avant** la compilation. Les instructions commencent par `#` sans point-virgule.
* **`<fichier.h>` vs `"fichier.h"` :** Chevrons pour le système, guillemets pour le projet local.
* **`#define` :** Remplacement textuel pur. Toujours parenthéser les arguments dans les macros (`((x) * (y))`).
* **Gardes d'inclusion (`#ifndef` / `#define` / `#endif`) :** Obligatoires dans **tous les fichiers `.h**` pour empêcher la ré-inclusion multiple.