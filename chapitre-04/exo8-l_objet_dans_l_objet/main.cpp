#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Objet {
    std::string nom;
    long long x;
    long long y;
    long long angle;
    long long echelle;
    long long profondeur;
};

long long normaliserAngle(long long angle) {
    angle %= 360;
    if (angle < 0) {
        angle += 360;
    }
    return angle;
}

int main() {
    int nombreObjets;
    if (!(std::cin >> nombreObjets)) {
        return 0;
    }

    std::vector<Objet> objets;
    std::unordered_map<std::string, std::size_t> indices;
    long long profondeurMax = 0;

    for (int i = 0; i < nombreObjets; ++i) {
        std::string nom;
        std::string nomParent;
        long long tx;
        long long ty;
        long long angle;
        long long echelle;

        std::cin >> nom >> nomParent >> tx >> ty >> angle >> echelle;

        Objet objet;
        objet.nom = nom;
        objet.angle = normaliserAngle(angle);
        objet.echelle = echelle;

        if (nomParent == "-") {
            objet.x = tx;
            objet.y = ty;
            objet.profondeur = 1;
        } else {
            const Objet& parent = objets[indices.at(nomParent)];

            const long long ax = tx * parent.echelle;
            const long long ay = ty * parent.echelle;
            long long rx;
            long long ry;

            if (parent.angle == 0) {
                rx = ax;
                ry = ay;
            } else if (parent.angle == 90) {
                rx = -ay;
                ry = ax;
            } else if (parent.angle == 180) {
                rx = -ax;
                ry = -ay;
            } else {
                rx = ay;
                ry = -ax;
            }

            objet.x = parent.x + rx;
            objet.y = parent.y + ry;
            objet.angle = normaliserAngle(parent.angle + objet.angle);
            objet.echelle *= parent.echelle;
            objet.profondeur = parent.profondeur + 1;
        }

        if (objet.profondeur > profondeurMax) {
            profondeurMax = objet.profondeur;
        }

        indices.emplace(nom, objets.size());
        objets.push_back(objet);

        std::cout << objet.nom << ' ' << objet.x << ' ' << objet.y << ' '
                  << objet.angle << ' ' << objet.echelle << '\n';
    }

    std::cout << "PROFONDEUR " << profondeurMax << '\n';
    return 0;
}