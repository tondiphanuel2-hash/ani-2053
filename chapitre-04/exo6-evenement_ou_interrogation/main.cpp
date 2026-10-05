#include <iostream>
#include <string>

int main() {
    long long vitesse;
    int nombreImages;

    if (!(std::cin >> vitesse >> nombreImages)) {
        return 0;
    }

    long long positionEvenements = 0;
    long long positionInterrogation = 0;
    long long sautsEvenements = 0;
    long long sautsInterrogation = 0;
    long long manques = 0;

    bool espaceEnfoncee = false;
    bool gaucheEnfoncee = false;
    bool droiteEnfoncee = false;

    for (int image = 1; image <= nombreImages; ++image) {
        int nombreEvenements;
        std::cin >> nombreEvenements;

        long long appuisEspaceDansImage = 0;

        for (int j = 0; j < nombreEvenements; ++j) {
            std::string evenement;
            std::cin >> evenement;

            if (evenement.size() < 2) {
                continue;
            }

            const char action = evenement[0];
            const std::string touche = evenement.substr(1);

            if (touche == "SPACE") {
                if (action == '+') {
                    ++sautsEvenements;
                    ++appuisEspaceDansImage;
                    espaceEnfoncee = true;
                } else if (action == '-') {
                    espaceEnfoncee = false;
                }
            } else if (touche == "RIGHT") {
                if (action == '+') {
                    positionEvenements += vitesse;
                    droiteEnfoncee = true;
                } else if (action == '-') {
                    droiteEnfoncee = false;
                }
            } else if (touche == "LEFT") {
                if (action == '+') {
                    positionEvenements -= vitesse;
                    gaucheEnfoncee = true;
                } else if (action == '-') {
                    gaucheEnfoncee = false;
                }
            }
        }

        if (appuisEspaceDansImage > 0 && !espaceEnfoncee) {
            manques += appuisEspaceDansImage;
        }

        if (espaceEnfoncee) {
            ++sautsInterrogation;
        }
        if (droiteEnfoncee) {
            positionInterrogation += vitesse;
        }
        if (gaucheEnfoncee) {
            positionInterrogation -= vitesse;
        }

        std::cout << image << ' ' << positionEvenements << ' '
                  << positionInterrogation << '\n';
    }

    std::cout << "SAUTS EVENEMENTS " << sautsEvenements << '\n';
    std::cout << "SAUTS INTERROGATION " << sautsInterrogation << '\n';
    std::cout << "MANQUES " << manques << '\n';

    return 0;
}