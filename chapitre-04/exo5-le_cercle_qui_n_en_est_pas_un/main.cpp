#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    int n;
    if (!(std::cin >> n)) {
        return 0;
    }

    int visibles = 0;
    int refuses = 0;
    constexpr double pi = 3.141592653589793;

    for (int i = 0; i < n; ++i) {
        long long rayon;
        long long segments;
        std::cin >> rayon >> segments;

        if (segments < 3) {
            std::cout << rayon << ' ' << segments << " REFUSE\n";
            ++refuses;
            continue;
        }

        const double angle = pi / static_cast<double>(segments);
        const double ecart = static_cast<double>(rayon) * (1.0 - std::cos(angle));

        if (ecart == 0.0) {
            std::cout << rayon << ' ' << segments << " 0 JAMAIS\n";
            continue;
        }

        const double ecartMillieme = std::floor(ecart * 1000.0);
        const double zoom = std::ceil(100.0 / ecart);

        std::cout << rayon << ' ' << segments << ' '
                  << std::fixed << std::setprecision(0) << ecartMillieme << ' '
                  << zoom << ' ';

        if (zoom <= 100.0) {
            std::cout << "VISIBLE\n";
            ++visibles;
        } else {
            std::cout << "INVISIBLE\n";
        }
    }

    std::cout << "VISIBLES " << visibles << '\n';
    std::cout << "REFUSES " << refuses << '\n';
    return 0;
}