#include <iostream>
#include <string>

int main() {
    int n;
    if (!(std::cin >> n)) {
        return 0;
    }

    long long totalPoints = 0;
    long long totalSegments = 0;
    long long totalTriangles = 0;
    long long totalRefuses = 0;

    for (int i = 0; i < n; ++i) {
        std::string type;
        long long sommets;
        std::cin >> type >> sommets;

        std::string unite;
        long long formes = 0;
        long long restants = 0;

        if (type == "POINTS") {
            unite = "POINTS";
            formes = sommets;
            totalPoints += formes;
        } else if (type == "LINES") {
            unite = "SEGMENTS";
            formes = sommets / 2;
            restants = sommets % 2;
            totalSegments += formes;
        } else if (type == "LINE_STRIP") {
            unite = "SEGMENTS";
            if (sommets >= 2) {
                formes = sommets - 1;
            } else {
                restants = sommets;
            }
            totalSegments += formes;
        } else if (type == "TRIANGLES") {
            unite = "TRIANGLES";
            formes = sommets / 3;
            restants = sommets % 3;
            totalTriangles += formes;
        } else if (type == "TRIANGLE_STRIP" || type == "TRIANGLE_FAN") {
            unite = "TRIANGLES";
            if (sommets >= 3) {
                formes = sommets - 2;
            } else {
                restants = sommets;
            }
            totalTriangles += formes;
        } else {
            std::cout << type << ' ' << sommets << " REFUSE\n";
            ++totalRefuses;
            continue;
        }

        std::cout << type << ' ' << sommets << ' ' << formes << ' '
                  << unite << ' ' << restants << '\n';
    }

    std::cout << "POINTS " << totalPoints << '\n';
    std::cout << "SEGMENTS " << totalSegments << '\n';
    std::cout << "TRIANGLES " << totalTriangles << '\n';
    std::cout << "REFUSES " << totalRefuses << '\n';

    return 0;
}