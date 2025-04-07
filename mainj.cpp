#include <iostream>
#include "DATE/Date.h"

int main() {
    try {
        // Test du constructeur par défaut
        Date defaultDate;
        std::cout << "Date par défaut: " << defaultDate << std::endl;

        // Test du constructeur avec paramètres
        Date specificDate(2024, 11, 29);
        std::cout << "Date spécifique: " << specificDate << std::endl;

        // Test des accesseurs
        std::cout << "Année: " << specificDate.getYear() << std::endl;
        std::cout << "Mois: " << specificDate.getMonth() << std::endl;
        std::cout << "Jour: " << specificDate.getDay() << std::endl;

        // Test de l'opérateur +=
        specificDate += 20;
        std::cout << "Après ajout de 20 jours: " << specificDate << std::endl;

        // Test de l'opérateur ++
        ++specificDate;
        std::cout << "Après incrémentation: " << specificDate << std::endl;

        // Test de l'opérateur +
        Date noel = specificDate + 5;
        std::cout << "Noël: " << noel << std::endl;
        std::cout << "La date originale reste: " << specificDate << std::endl;

        // Test des opérateurs de comparaison
        Date date1(2024, 12, 15);
        Date date2(2024, 12, 25);
        std::cout << "date1 < date2: " << (date1 < date2 ? "vrai" : "faux") << std::endl;
        std::cout << "date1 == date2: " << (date1 == date2 ? "vrai" : "faux") << std::endl;

        // Test de dates hors limites
        try {
            Date invalidDate(2023, 10, 1); // Avant la plage
            std::cout << "Cette ligne ne devrait pas s'afficher!" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Exception attendue: " << e.what() << std::endl;
        }

        try {
            Date invalidDate(2025, 3, 1); // Après la plage
            std::cout << "Cette ligne ne devrait pas s'afficher!" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Exception attendue: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
