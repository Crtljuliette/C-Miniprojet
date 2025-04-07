#include <iostream>
#include "DATE/Date.cpp"

int main() {
    try {
        // Test du constructeur par défaut
        Date defaultDate;
        std::cout << "Date par défaut: " << defaultDate << std::endl;

        // Test du constructeur avec paramètres
        Date specificDate(2024, 11, 29);
        std::cout << "Date spécifique: " << specificDate << std::endl;

        // Test des opérateurs comme dans l'énoncé
        std::cout << "Test des opérateurs selon l'énoncé:" << std::endl;
        Date d(2024, 11, 29);  // 29 novembre 2024
        std::cout << "Date initiale: " << d << std::endl;

        d += 20;
        std::cout << "Après d += 20: " << d << std::endl;  // 19 décembre 2024

        ++d;
        std::cout << "Après ++d: " << d << std::endl;  // 20 décembre 2024

        Date noel = d + 5;
        std::cout << "noel = d + 5: " << noel << std::endl;  // 25 décembre 2024
        std::cout << "d reste: " << d << std::endl;  // toujours 20 décembre 2024

        // Test des opérateurs de comparaison
        std::cout << "Test des opérateurs de comparaison:" << std::endl;
        std::cout << "d < noel: " << (d < noel ? "vrai" : "faux") << std::endl;
        std::cout << "noel < d: " << (noel < d ? "vrai" : "faux") << std::endl;
        std::cout << "d == d: " << (d == d ? "vrai" : "faux") << std::endl;
        std::cout << "d == noel: " << (d == noel ? "vrai" : "faux") << std::endl;

        // Test date invalide
        std::cout << "Test date invalide:" << std::endl;
        Date invalidDate(2024, 2, 29);
        std::cout << "Date invalide: " << invalidDate << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}