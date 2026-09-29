# La Gestion du Temps en Langage C et en Informatique

La mesure du temps sur un ordinateur repose sur deux approches fondamentales : une représentation **linéaire** (un simple compteur continu) idéale pour les machines, et une représentation **calendaire** (années, mois, jours, heures) adaptée aux humains.

Le langage C fournit les outils standards pour manipuler ces deux représentations à travers la bibliothèque **`<time.h>`**.

---

## 1. L'Origine du Timestamp POSIX (L'Époque Unix)

### Qu'est-ce que le Timestamp Unix ?

Le **Timestamp POSIX** (ou *Unix Epoch*) représente le nombre de secondes écoulées depuis le **1er janvier 1970 à 00:00:00 UTC** (temps universel coordonné). En C, cette valeur est stockée sous le type `time_t`.

### Pourquoi le 1er janvier 1970 ? (Raisons historiques)

1. **L'émergence d'Unix :** À la fin des années 1960, les ingénieurs d'AT&T Bell Labs (notamment Ken Thompson et Dennis Ritchie, également créateur du langage C) développent le système d'exploitation Unix. Il leur faut un repère temporel universel, simple et léger pour horodater les fichiers (*timestamps* de modification) et ordonnancer les processus.
2. **La simplicité de calcul :** Un simple entier s'incrémentant chaque seconde évite de gérer en permanence la complexité des années bissextiles, des mois à durée variable et des fuseaux horaires dans le noyau du système.
3. **Le choix de la date :** La date du 1er janvier 1970 à 00:00:00 UTC a été choisie arbitrairement comme une date récente et ronde au moment où le système Unix a été formalisé (au tout début des années 1970).

> ⚠️ **Le bug de l'an 2038 (*Y2K38 Problem*) :**
> Sur les systèmes 32 bits historiques, `time_t` est stocké sous forme d'un entier signé sur 32 bits (`int32_t`). La valeur maximale possible est $2\ 147\ 483\ 647$, ce qui correspond exactement au **19 janvier 2038 à 03:14:07 UTC**.
> Dépasser cette limite provoque un dépassement de capacité (*overflow*) et fait repartir le compteur en négatif vers l'année 1901. Les mises à jour des systèmes 32 bits ont consisté à modifier le code pour gérer les timestamps sur 64 bits, repoussant ainsi l'échéance à plusieurs centaines de milliards d'années.

---

## 2. La Structure `struct tm` et la particularité de l'année 1900

Pour convertir le timestamp brut en une date lisible par un humain, le C utilise la structure **`struct tm`**.

### Décomposition de `struct tm`

```c
struct tm {
    int tm_sec;   // Secondes [0, 60] (60 permet de gérer les secondes intercalaires)
    int tm_min;   // Minutes [0, 59]
    int tm_hour;  // Heures [0, 23]
    int tm_mday;  // Jour du mois [1, 31]
    int tm_mon;   // Mois de l'année [0, 11]  <-- Attention : Janvier = 0 !
    int tm_year;  // Années écoulées depuis 1900 <-- Attention : Décalage !
    int tm_wday;  // Jour de la semaine [0, 6] (Dimanche = 0)
    int tm_yday;  // Jour dans l'année [0, 365]
    int tm_isdst; // Fanion d'heure d'été (>0 si actif, 0 si inactif, <0 si inconnu)
};

```

---

### Pourquoi `tm_year` compte-t-il à partir de 1900 et non de 1970 ?

C'est une confusion fréquente : le **Timestamp** utilise l'origine **1970**, mais **`struct tm`** utilise le repère **1900**.

#### 1. L'explication historique (Les cartes perforées et le XXᵉ siècle)

Lorsque la bibliothèque C standard a été conçue, la mémoire informatique était extrêmement précieuse et mesurée en octets. Pour stocker l'année dans un espace réduit (par exemple sur un octet ou dans des formats de paquets très stricts) et éviter de manipuler des nombres à 4 chiffres (comme `1973`), les concepteurs ont choisi de stocker uniquement le **nombre d'années écoulées depuis le début du XXᵉ siècle (1900)**.

* L'année 1973 était ainsi stockée sous la forme `73`.
* L'année 1998 était stockée sous la forme `98`.

> ⚠️ **Bug de l'an 2000 (*Y2K*)** : Cette approche a conduit à des problèmes de compatibilité avec les systèmes anciens, car les années `00` à `99` pouvaient être interprétées comme 1900-1999 au lieu de 2000-2099. C'est pourquoi de nombreux systèmes ont dû être mis à jour pour gérer correctement le passage à l'an 2000. Ces mises à jour ont consisté à ajouter des règles de conversion ou à utiliser des types de données plus grands pour stocker l'année complète.

#### 2. L'explication technique (Antériorité par rapport à Unix)

La notation décalée par rapport à 1900 existait dans les conventions de programmation du langage B et de FORTRAN bien avant la création du système Unix et le choix du timestamp au 1er janvier 1970.

#### 3. Comment effectuer les conversions en C ?

Pour afficher ou manipuler l'année réelle dans le code, il faut obligatoirement rajouter $1900$ lors de la lecture, et soustraire $1900$ lors de la définition d'une date :

```c
// LECTURE : Obtenir l'année courante (ex: pour 2026)
// tm_year contient le nombre d'années écoulées depuis 1900
int annee_reelle = moment->tm_year + 1900; // 126 + 1900 = 2026

// ÉCRITURE : Définir une date spécifique (ex: l'année 2030)
struct tm ma_date = {0};
ma_date.tm_year = 2030 - 1900; // On stocke 130

```

---

## 3. Les Fonctions Principales de `<time.h>`

| Fonction | Description | Entrée / Sortie |
| --- | --- | --- |
| **`time()`** | Récupère le timestamp UTC actuel du système. | `NULL` $\rightarrow$ `time_t` |
| **`localtime()`** | Convertit un timestamp en `struct tm` selon le fuseau horaire local. | `time_t*` $\rightarrow$ `struct tm*` |
| **`gmtime()`** | Convertit un timestamp en `struct tm` exprimé en heure UTC (sans fuseau). | `time_t*` $\rightarrow$ `struct tm*` |
| **`mktime()`** | Opération inverse : convertit une `struct tm` en timestamp `time_t`. | `struct tm*` $\rightarrow$ `time_t` |
| **`strftime()`** | Formate une `struct tm` en une chaîne de texte personnalisée (façon `printf`). | `struct tm*` $\rightarrow$ `char[]` |
| **`clock()`** | Mesure le temps CPU consommé par le processus (pour le profilage). | Aucun $\rightarrow$ `clock_t` |

---

## Récapitulatif

* **Timestamp (`time_t`) :** Nombre de secondes depuis le **1er janvier 1970 à 00:00:00 UTC**.
* **Structure calendaire (`struct tm`) :**
* `tm_year` : Année réelle **$- 1900$** (Héritage du XXᵉ siècle).
* `tm_mon` : Mois de **0 à 11** (Janvier $= 0$).
* `tm_mday` : Jour du mois de **1 à 31**.


* **Formatage :** Préférer toujours `strftime()` pour afficher proprement une date sur mesure.