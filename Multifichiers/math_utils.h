/*
 ============================================================================
                               HEADER FILE
 ============================================================================  
Il s'agit d'un fichier d'en-tête (header file), il contient les 
déclarations (prototypes)

Ce fichier sert de « carte de visite » ou de contrat. Il indique aux autres 
fichiers quelles fonctions et structures sont disponibles, sans en révéler 
le code interne.
*/

// ----------------------------------------------------
// GARDES D'INCLUSION (Include Guards)
// Empêchent l'inclusion multiple de ce fichier lors de la compilation.
// ----------------------------------------------------
#ifndef MATH_UTILS_H // Vérifie si MATH_UTILS_H n'est pas défini
#define MATH_UTILS_H // Définit MATH_UTILS_H pour éviter les inclusions multiples

// Déclaration des prototypes de fonctions
int additionner(int a, int b);
double calculer_moyenne(int tableau[], int taille);

#endif // MATH_UTILS_H