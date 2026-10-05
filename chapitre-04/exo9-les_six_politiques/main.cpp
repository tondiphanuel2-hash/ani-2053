#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Politique {
    std::string nom;
    long long vx;
    long long vy;
    long long vw;
    long long vh;
    long long mw;
    long long mh;
};

long long arrondir(long long numerateur, long long denominateur) {
    return (2 * numerateur + denominateur) / (2 * denominateur);
}

Politique letterbox(long long rw, long long rh, long long w, long long h) {
    long long vw;
    long long vh;

    if (w * rh <= h * rw) {
        vw = w;
        vh = arrondir(rh * w, rw);
    } else {
        vh = h;
        vw = arrondir(rw * h, rh);
    }

    return {"FIT_LETTERBOX", (w - vw) / 2, (h - vh) / 2,
            vw, vh, rw, rh};
}

int main() {
    long long rw;
    long long rh;
    long long aw;
    long long ah;
    long long w;
    long long h;

    if (!(std::cin >> rw >> rh >> aw >> ah >> w >> h)) {
        return 0;
    }

    const bool referencePresente = rw > 0 && rh > 0;
    std::vector<Politique> politiques;

    politiques.push_back({"FOLLOW_WINDOW", 0, 0, w, h, w, h});

    if (!referencePresente) {
        politiques.push_back({"STRETCH", 0, 0, w, h, w, h});
        politiques.push_back({"FIT_LETTERBOX", 0, 0, w, h, w, h});
        politiques.push_back({"INTEGER_SCALE", 0, 0, w, h, w, h});
        politiques.push_back({"FIT_CROP", 0, 0, w, h, w, h});
    } else {
        politiques.push_back({"STRETCH", 0, 0, w, h, rw, rh});
        politiques.push_back(letterbox(rw, rh, w, h));

        if (w >= rw && h >= rh) {
            const long long echelle = std::min(w / rw, h / rh);
            const long long vw = rw * echelle;
            const long long vh = rh * echelle;

            politiques.push_back({"INTEGER_SCALE", (w - vw) / 2,
                                  (h - vh) / 2, vw, vh, rw, rh});
        } else {
            Politique politique = letterbox(rw, rh, w, h);
            politique.nom = "INTEGER_SCALE";
            politiques.push_back(politique);
        }

        long long mw;
        long long mh;

        if (w * rh > h * rw) {
            mw = rw;
            mh = arrondir(rw * h, w);
        } else {
            mw = arrondir(rh * w, h);
            mh = rh;
        }

        politiques.push_back({"FIT_CROP", 0, 0, w, h, mw, mh});
    }

    politiques.push_back({"MANUAL", 0, 0, aw, ah, aw, ah});

    long long bandes = 0;
    for (const Politique& politique : politiques) {
        std::cout << politique.nom << ' '
                  << politique.vx << ' ' << politique.vy << ' '
                  << politique.vw << ' ' << politique.vh << ' '
                  << politique.mw << ' ' << politique.mh << '\n';

        if (politique.vw < w || politique.vh < h) {
            ++bandes;
        }
    }

    std::cout << "BANDES " << bandes << '\n';

    const bool deformation = referencePresente && w * rh != h * rw;
    std::cout << "DEFORMATION " << (deformation ? "OUI" : "NON") << '\n';

    return 0;
}