#include <iostream>

int main() {
    long long colonnes;
    long long lignes;
    long long largeur;
    long long hauteur;
    long long nombreCases;
    long long dureeCase;
    long long plafond;

    if (!(std::cin >> colonnes >> lignes >> largeur >> hauteur
                   >> nombreCases >> dureeCase >> plafond)) {
        return 0;
    }

    long long nombreImages;
    std::cin >> nombreImages;

    long long caseCourante = 0;
    long long tempsAccumule = 0;
    long long avances = 0;
    long long plafonnes = 0;

    for (long long i = 0; i < nombreImages; ++i) {
        long long dt;
        std::cin >> dt;

        if (dt > plafond) {
            dt = plafond;
            ++plafonnes;
        }

        tempsAccumule += dt;
        const long long passages = tempsAccumule / dureeCase;
        tempsAccumule %= dureeCase;

        avances += passages;
        caseCourante = (caseCourante + passages % nombreCases) % nombreCases;

        const long long x = (caseCourante % colonnes) * largeur;
        const long long y = (caseCourante / colonnes) * hauteur;

        std::cout << caseCourante << ' ' << x << ' ' << y << ' '
                  << largeur << ' ' << hauteur << '\n';
    }

    std::cout << "AVANCES " << avances << '\n';
    std::cout << "PLAFONNES " << plafonnes << '\n';

    return 0;
}