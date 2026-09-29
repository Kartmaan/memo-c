#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Indispensable pour les fonctions mathématiques standards

// Définition d'une constante pour Pi si elle n'est pas fournie par math.h (M_PI)
#ifndef M_PI // Vérifie si M_PI est déjà défini
#define M_PI 3.14159265358979323846 // Définition de Pi avec une précision suffisante
#endif // Permet de s'assurer que M_PI n'est défini qu'une seule fois

// Fonction utilitaire pour calculer un logarithme dans une base quelconque
// Formule du changement de base : log_b(x) = ln(x) / ln(b)
double log_base(double x, double base) {
    return log(x) / log(base);
}

int main(void) {
    printf("=== RACINE CARRÉE ET PUISSANCES ===\n");
    double x = 2.0;
    double racine = sqrt(x);        // Racine carrée : sqrt(x)
    double puissance = pow(x, 3.0); // Puissance : x^3

    printf("sqrt(%.1f) = %.6f\n", x, racine);
    printf("%.1f^3 = %.1f\n\n", x, puissance);

    printf("=== LOGARITHMES ET EXPONENTIELLE ===\n");
    double val = 100.0;
    
    double ln_val = log(val);        // Logarithme naturel / népérien (base e)
    double log10_val = log10(val);   // Logarithme en base 10
    double log2_val = log2(val);     // Logarithme en base 2
    double exp_val = exp(1.0);       // Exponentielle e^1

    printf("ln(%.1f) = %.4f\n", val, ln_val);
    printf("log10(%.1f) = %.2f\n", val, log10_val);
    printf("log2(%.1f) = %.4f\n", val, log2_val);
    printf("log_base_5(%.1f) = %.4f\n", val, log_base(val, 5.0));
    printf("e^1 (Constante d'Euler) = %.6f\n\n", exp_val);

    printf("=== TRIGONOMÉTRIE (Radian) ===\n");
    // /!\ Les fonctions trigonométriques travaillent TOUJOURS en radians !
    double angle_degres = 45.0;
    double angle_radians = angle_degres * (M_PI / 180.0); // Conversion Degrés -> Radians

    printf("Angle : %.1f degres = %.4f radians\n", angle_degres, angle_radians);
    printf("sin(45°) = %.4f\n", sin(angle_radians));
    printf("cos(45°) = %.4f\n", cos(angle_radians));
    printf("tan(45°) = %.4f\n\n", tan(angle_radians));

    printf("=== NOTATION SCIENTIFIQUE DANS PRINTF ===\n");
    double constante_planck = 6.62607015e-34; // 6.626 x 10^-34
    double vitesse_lumiere = 299792458.0;     // ~3.00 x 10^8
    double masse_terre = 5.972e24;            // 5.972 x 10^24

    // %e : Affichage en notation scientifique (minuscule 'e')
    // %E : Affichage en notation scientifique (majuscule 'E')
    // %g : Choisit automatiquement le format le plus court entre %f et %e
    printf("Constante de Planck (%%e) : %e J.s\n", constante_planck);
    printf("Constante de Planck (%%.2E) : %.2E J.s\n", constante_planck);
    printf("Vitesse de la lumiere (%%e)  : %e m/s\n", vitesse_lumiere);
    printf("Masse de la Terre (%%g)      : %g kg\n\n", masse_terre);

    printf("=== ARRONDI ET VALEUR ABSOLUE ===\n");
    double nombre_negatif = -5.75;

    printf("fabs(%.2f)   = %.2f (Valeur absolue pour flottant)\n", nombre_negatif, fabs(nombre_negatif));
    printf("floor(%.2f)  = %.2f (Arrondi vers le bas / Plancher)\n", nombre_negatif, floor(nombre_negatif));
    printf("ceil(%.2f)   = %.2f (Arrondi vers le haut / Plafond)\n", nombre_negatif, ceil(nombre_negatif));
    printf("round(%.2f)  = %.2f (Arrondi au plus proche)\n", nombre_negatif, round(nombre_negatif));

    return 0;
}