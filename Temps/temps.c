#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    // ====================================================
    // OBTENIR LE TIMESTAMP ACTUEL (time_t)
    // ====================================================
    printf("=== 1. TIMESTAMP BRUT ===\n");

    // time(NULL) renvoie le nombre de secondes depuis le 01/01/1970
    // NULL signifie que l'on ne souhaite pas stocker le résultat dans une variable struct tm
    time_t timestamp_actuel = time(NULL);

    // Dans certains cas, time() peut échouer et renvoyer (time_t)-1
    if (timestamp_actuel == (time_t)-1) {
        fprintf(stderr, "Erreur : Impossible d'obtenir le temps actuel.\n");
        return 1;
    }

    printf("Timestamp (secondes depuis 1970) : %ld s\n\n", (long)timestamp_actuel);

    // ====================================================
    // CONVERTIR LE TIMESTAMP EN STRUCTURE (struct tm)
    // ====================================================
    printf("=== 2. DATE ET HEURE DÉCOMPOSÉES ===\n");

    // Nous déclarons un struct tm pour stocker la date et l'heure décomposées
    // struct tm est une structure définie dans <time.h> qui contient les champs suivants :
    // int tm_sec;   // secondes après la minute (0-60)
    // int tm_min;   // minutes après l'heure (0-59)
    // int tm_hour;  // heures depuis minuit (0-23)
    // int tm_mday;  // jour du mois (1-31)
    // int tm_mon;   // mois depuis janvier (0-11)
    // int tm_year;  // années depuis 1900
    //
    // moment_local est un pointeur vers une structure tm qui sera remplie par localtime()
    // localtime() convertit le timestamp selon le fuseau horaire local
    // Nous accédons à la valeur timestamp_actuel via l'adresse (&timestamp_actuel)
    struct tm *moment_local = localtime(&timestamp_actuel);

    // /!\ ATTENTION AUX DÉCALAGES HISTORIQUES DE STRUCT TM :
    // - moment_local->tm_year contient la valeur de l'année en cours MOINS 1900 
    // (ex: 126 pour 2026 car 2026 - 1900 = 126). La raison est que struct tm a été conçu 
    //pour être compatible avec les années depuis 1900.
    // - moment_local->tm_mon va de 0 (janvier) à 11 (décembre)
    // L'opérateur -> permet d'accéder aux champs de la structure pointée par moment_local
    int annee   = moment_local->tm_year + 1900;
    int mois    = moment_local->tm_mon + 1; // Ajustement 1-12 car le mois est indexé à partir de 0
    int jour    = moment_local->tm_mday;
    int heure   = moment_local->tm_hour;
    int minute  = moment_local->tm_min;
    int seconde = moment_local->tm_sec;

    printf("Date locale : %02d/%02d/%04d\n", jour, mois, annee);
    printf("Heure locale: %02d:%02d:%02d\n\n", heure, minute, seconde);

    // ====================================================
    // FORMATER UNE DATE EN CHAÎNE (strftime)
    // ====================================================
    printf("=== 3. FORMATAGE PERSONNALISÉ (strftime) ===\n");

    char buffer_date[100];

    // strftime permet de construire une chaîne de caractères sur mesure :
    // %d : jour (01..31)  | %m : mois (01..12)  | %Y : année complète
    // %H : heure (00..23) | %M : minute (00..59)| %S : seconde (00..59)
    // %A : nom du jour    | %B : nom du mois
    strftime(buffer_date, sizeof(buffer_date), "%A %d %B %Y - %H:%M:%S", moment_local);
    printf("Format texte : %s\n\n", buffer_date);

    // ====================================================
    // MESURER LE TEMPS D'EXÉCUTION (clock)
    // ====================================================
    printf("=== 4. MESURE DE PERFORMANCES (clock) ===\n");

    // clock() mesure le temps CPU consommé par le programme en "ticks"
    clock_t debut = clock();

    // Simulation d'un calcul intensif
    double calcul = 0.0;
    for (long i = 0; i < 50000000; i++) {
        calcul += i * 0.1;
    }

    clock_t fin = clock();

    // Conversion des ticks CPU en secondes réelles
    double temps_cpu = (double)(fin - debut) / CLOCKS_PER_SEC;
    printf("Temps d'execution CPU : %.4f secondes (Calcul = %.1f)\n\n", temps_cpu, calcul);

    // ====================================================
    // RECONSTRUIRE UN TIMESTAMP À PARTIR D'UNE DATE (mktime)
    // ====================================================
    printf("=== 5. CRÉER UNE DATE SPÉCIFIQUE (mktime) ===\n");

    struct tm date_perso = {0};
    date_perso.tm_year = 2030 - 1900; // Année 2030
    date_perso.tm_mon  = 0;           // Janvier (index 0)
    date_perso.tm_mday = 1;           // 1er du mois
    date_perso.tm_hour = 12;          // 12h00
    date_perso.tm_min  = 0;
    date_perso.tm_sec  = 0;

    // mktime calcule le timestamp correspondant et réajuste la structure tm
    time_t timestamp_futur = mktime(&date_perso);
    printf("Timestamp du 01/01/2030 : %ld s\n", (long)timestamp_futur);

    // difftime calcule la différence exacte en secondes entre deux time_t
    double diff_secondes = difftime(timestamp_futur, timestamp_actuel);
    printf("Secondes d'ici le 01/01/2030 : %.0f s (~%.1f jours)\n", 
           diff_secondes, diff_secondes / (3600 * 24));

    return 0;
}