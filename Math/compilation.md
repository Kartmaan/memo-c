Commande pour compiler : 
```bash
gcc mathematics.c -o mathematics -lm
```

L'option **`-lm`** indique au compilateur (ou plus exactement à l'**éditeur de liens**, le *linker*) d'inclure la **bibliothèque mathématique standard** lors de la création de l'exécutable.

---

### Que signifie exactement `-lm` ?

La syntaxe `-l` est une option standard de GCC et Clang pour lier une bibliothèque dynamique ou statique :

* Le **`-l`** signifie *« link »* (lier).
* Le **`m`** est le nom court de la bibliothèque : **`libm`** (la *Math library*).

Lorsqu'on écrit `-lm`, l'éditeur de liens cherche le fichier système `libm.so` (sous Linux) ou `libm.a` pour y récupérer le code compilé des fonctions mathématiques.

---

### Pourquoi `#include <math.h>` ne suffit-il pas ?

C'est une distinction fondamentale en C entre **déclaration** et **définition** :

1. **`#include <math.h>` (Fichier d'en-tête) :** Il donne uniquement les **prototypes** des fonctions au compilateur (ex. : *"la fonction `sqrt` prend un `double` et renvoie un `double`"*). Cela permet au compilateur de vérifier la syntaxe de ton code.
2. **`-lm` (Bibliothèque binaire) :** Il fournit le **code exécutable réel** (le binaire compilé) des fonctions comme `sqrt()`, `pow()`, `sin()`, etc.

Sans `-lm`, la compilation passe la phase syntaxique, mais l'éditeur de liens échoue avec une erreur du type :
`undefined reference to 'sqrt'` ou `référence indéfinie vers « sqrt »`.

---

### Est-elle spécifique à `math.h` ?

**Oui, `-lm` est spécifiquement dédiée à `libm` (et donc `<math.h>`).**

Cependant, le mécanisme du drapeau **`-l`** est universel et s'utilise pour n'importe quelle bibliothèque externe :

* **`-lm`** $\rightarrow$ lie `libm` (`<math.h>`)
* **`-lpthread`** $\rightarrow$ lie `libpthread` (`<pthread.h>` pour le multithreading)
* **`-lcurl`** $\rightarrow$ lie `libcurl` (`<curl/curl.h>` pour les requêtes HTTP)
* **`-lssl`** $\rightarrow$ lie `libssl` (OpenSSL)

---

### Pourquoi la bibliothèque C de base (`libc`) n'a-t-elle pas besoin d'option ?

Des fonctions comme `printf()`, `scanf()` ou `malloc()` sont déclarées dans `<stdio.h>` ou `<stdlib.h>`. Elles font partie de la bibliothèque C principale (**`libc`**).

GCC lie **automatiquement** `libc` (ce qui équivaudrait à un `-lc` implicite) à chaque compilation. En revanche, pour des raisons historiques d'optimisation de la taille des exécutables sous Unix, la bibliothèque mathématique `libm` a été séparée et doit être demandée explicitement avec `-lm`.

> 💡 **Remarque :** L'option `-lm` doit toujours être placée **à la fin** de la commande de compilation :
> ```bash
> gcc mon_programme.c -o mon_programme -lm
> 
> ```