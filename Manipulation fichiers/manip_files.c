#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *nom_fichier = "mon_fichier.txt";

    // ----------------------------------------------------
    // 1. VÉRIFICATION DE L'EXISTENCE DU FICHIER
    // ----------------------------------------------------
    printf("=== 1. VÉRIFICATION D'EXISTENCE ===\n");

    // L'option "r" (read) échoue et renvoie NULL si le fichier n'existe pas.
    FILE *test_existence = fopen(nom_fichier, "r");

    if (test_existence != NULL) {
        printf("Le fichier '%s' existe deja.\n", nom_fichier);
        fclose(test_existence); // Ne pas oublier de le fermer apres le test !
    } else {
        printf("Le fichier '%s' n'existe pas encore. Il va etre cree.\n", nom_fichier);
    }

    // ----------------------------------------------------
    // 2. CRÉATION / SUPPRESSION DU CONTENU & ÉCRITURE
    // ----------------------------------------------------
    printf("\n=== 2. CRÉATION ET ÉCRITURE (Mode 'w') ===\n");

    // Le mode "w" (write) :
    // - Crée le fichier s'il n'existe pas.
    // - ÉCRASE / EFFACE intégralement le contenu s'il existait déjà.
    FILE *fichier_ecriture = fopen(nom_fichier, "w");

    // Test de sécurité obligatoire : vérifier si l'ouverture a réussi
    if (fichier_ecriture == NULL) {
        fprintf(stderr, "Erreur : Impossible de créer/ouvrir le fichier !\n");
        return 1;
    }

    // Écriture de texte avec fprintf()
    fprintf(fichier_ecriture, "Ligne 1 : Début du fichier memo C.\n");
    fprintf(fichier_ecriture, "Ligne 2 : Les pointeurs et les fichiers sont maitrises.\n");
    fprintf(fichier_ecriture, "Ligne 3 : Fin du test d'ecriture.\n");

    // Fermeture du fichier (sauvegarde les données sur le disque)
    fclose(fichier_ecriture);
    printf("Ecriture terminee et fichier enregistre.\n");

    // ----------------------------------------------------
    // 3. LECTURE DU CONTENU DU FICHIER
    // ----------------------------------------------------
    printf("\n=== 3. LECTURE DU FICHIER (Mode 'r') ===\n");

    FILE *fichier_lecture = fopen(nom_fichier, "r");

    if (fichier_lecture == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier en lecture !\n");
        return 1;
    }

    // Tampon (buffer) pour lire le fichier ligne par ligne
    char ligne[256];

    printf("--- CONTENU DU FICHIER --- \n");
    // fgets() lit une ligne jusqu'au saut de ligne '\n' ou jusqu'a la fin du fichier (EOF).
    // Elle renvoie NULL lorsqu'il n'y a plus rien a lire.
    while (fgets(ligne, sizeof(ligne), fichier_lecture) != NULL) {
        printf("%s", ligne);
    }
    printf("---------------------------\n");

    // Fermeture du fichier
    fclose(fichier_lecture);

    return 0;
}