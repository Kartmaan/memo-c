# Comprendre l'Allocation Dynamique de Mémoire en C

Déclarer une variable en faisant par exemple `int a;` ou `char tab[10];` réserve de la mémoire **à la compilation**. La taille de ces variables est **fixe** et ne peut pas être modifiée pendant l'exécution du programme. Mais il arrive que l'on ait besoin de créer des tableaux dont la taille n'est pas connue à l'avance, ou qui doit pouvoir changer pendant l'exécution. C'est là qu'intervient l'**allocation dynamique**.

L'**allocation dynamique** permet au programme de demander de la mémoire au système d'exploitation **pendant son exécution**, en fonction des besoins réels (par exemple, la taille d'un fichier ouvert ou un choix saisi par l'utilisateur).

---

## 1. La Pile (Stack) vs Le Tas (Heap)

Pour bien comprendre la mémoire en informatique, il faut savoir qu'elle est divisée en deux zones principales :

```
     MÉMOIRE RAM
+--------------------+
|     LA PILE        |  <-- Automatique, rapide, taille fixe
|     (STACK)        |      (Variables locales, int a, char tab[10])
+--------------------+
|                    |
|      LE TAS        |  <-- Manuel, flexible, très grand
|      (HEAP)        |      (Réservé à la demande avec malloc)
+--------------------+

```

### La Pile (*Stack*)

* **Fonctionnement :** Automatique. Quand on déclare `int age = 20;` dans une fonction, la variable est placée sur la pile. Dès que la fonction se termine, la mémoire est automatiquement nettoyée.
* **Avantage :** Ultra-rapide et totalement transparente.
* **Inconvénient :** Taille très limitée. Impossible de modifier la taille d'un tableau une fois créé.

### Le Tas (*Heap*)

* **Fonctionnement :** Manuel. C'est un grand espace mémoire disponible. On doit réserver nous-même notre espace avec `malloc()` et le libérer nous-même avec `free()`.
* **Avantage :** Permet de créer des tableaux de n'importe quelle taille, ajustables à volonté pendant l'exécution.
* **Inconvénient :** L'oubli de nettoyage crée des **fuites de mémoire** (*memory leaks*).

---

## 2. Les Fonctions Clés de `<stdlib.h>`

Pour manipuler le *Heap*, on utilise quatre fonctions fournies par la bibliothèque **`<stdlib.h>`** :

| Fonction | Rôle principal | Syntaxe type |
| --- | --- | --- |
| **`malloc()`** | Réserve un espace mémoire en octets. Contenu non initialisé (données aléatoires). | `int *p = malloc(5 * sizeof(int));` |
| **`calloc()`** | Réserve un espace mémoire et l'initialise entièrement avec des zéros. | `int *p = calloc(5, sizeof(int));` |
| **`realloc()`** | Agrandit ou rétrécit un bloc mémoire déjà existant. | `int *tmp = realloc(p, 10 * sizeof(int));` |
| **`free()`** | Libère la mémoire réservée pour la rendre au système. | `free(p);` |

---

## 3. Les 3 Règles d'Or (Bonnes Pratiques)

### 1. Toujours utiliser `sizeof()`

La taille d'un type (`int`, `double`, etc.) dépend du processeur et du système. Ne jamais calculer les octets "à la main" (ex: écrire `40` pour 10 entiers).

> **Bonne pratique :** Multiplie toujours le nombre d'éléments souhaité par `sizeof(type)`.
> ```c
> int *tab = malloc(10 * sizeof(int)); // Réserve exactement l'espace pour 10 entiers
> 
> ```
> 
> 

### 2. Le Test de Sécurité OBLIGATOIRE (Vérification de `NULL`)

Si la mémoire de l'ordinateur est saturée, `malloc()` échoue et renvoie un pointeur égal à `NULL`. Tenter de lire ou d'écrire sur un pointeur `NULL` fait immédiatement planter le programme (*Segmentation Fault*).

> **Bonne pratique :** On teste **systématiquement** le retour de `malloc()` avant d'utiliser le pointeur.
> ```c
> int *p = malloc(5 * sizeof(int));
> if (p == NULL) {
>     // Gestion de l'erreur
>     printf("Erreur : Mémoire saturée !\n");
>     return 1; // On arrête le programme
> }
> 
> ```
> 
> 

### 3. La règle du nettoyage : Un `malloc` = Un `free`

Toute mémoire allouée dynamiquement reste occupée dans la RAM jusqu'à ce qu'on libère explicitement, ou jusqu'à la fermeture complète du programme.

> **Bonne pratique :**
> 1. Dès qu'on a plus besoin de la mémoire, appelle `free(p);`.
> 2. On remet immédiatement le pointeur à `NULL` (`p = NULL;`). Cela évite de réutiliser par erreur une adresse mémoire libérée (ce qu'on appelle un *pointeur sauvage* ou *dangling pointer*).
> 
> 

---

## 4. Schéma Récapitulatif du Cycle de Vie

```
  1. Réservation            2. Sécurité              3. Utilisation            4. Nettoyage
+----------------+      +----------------+      +----------------+      +----------------+
| p = malloc(...)| ---> | if (p != NULL) | ---> | p[0] = 12;     | ---> | free(p);       |
+----------------+      +----------------+      +----------------+      | p = NULL;      |
                                                                        +----------------+

```