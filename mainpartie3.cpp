#include <iostream>
#include <string>
#include <sstream>
#include "Date.h"
#include "Databank.h"
#include "RadarImage.h"
#include "SimplePixel.h"
#include "AveragePixel.h"

// Fonction pour construire le nom de fichier radar à partir d'une date
std::string generateRadarFilename(Date& date) {
    std::ostringstream oss;
    // Formatage de l'année
    oss << "radar/" << date.getYear() << "-";
    // Formatage du mois sur deux chiffres
    if (date.getMonth() < 10) oss << "0";
    oss << date.getMonth() << "-";
    // Formatage du jour sur deux chiffres
    if (date.getDay() < 10) oss << "0";
    oss << date.getDay();
    oss << ".tif";
    return oss.str();
}

int main(int argc, char** argv) {
    // Vérifier les arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <date:YYYY-MM-DD> <algorithme:1|2>" << std::endl;
        std::cerr << "  1: SimplePixel, 2: AveragePixel" << std::endl;
        return 1;
    }

    // Analyser la date
    std::string dateStr = argv[1];
    int year, month, day;
    if (sscanf(dateStr.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
        std::cerr << "Format de date invalide. Utilisez YYYY-MM-DD." << std::endl;
        return 1;
    }

    // Créer l'objet Date avec les valeurs parsées
    Date date(year, month, day);

    // Analyser le choix d'algorithme
    int algoChoice;
    try {
        algoChoice = std::stoi(argv[2]);
        if (algoChoice != 1 && algoChoice != 2) {
            throw std::invalid_argument("Choix d'algorithme invalide");
        }
    } catch (const std::exception& e) {
        std::cerr << "Choix d'algorithme invalide. Utilisez 1 pour SimplePixel ou 2 pour AveragePixel." << std::endl;
        return 1;
    }

    try {
        // Charger les données
        Databank databank("stations.csv", "donnees.csv");

        // Construire le nom du fichier radar et le charger
        std::string radarFilename = generateRadarFilename(date);
        RadarImage radarImage(radarFilename);

        if (!radarImage.isValid()) {
            std::cerr << "Erreur: Image radar non valide pour la date " << date << std::endl;
            return 1;
        }

        // Créer l'algorithme approprié
        ComparisonAlgorithm* algorithm = nullptr;
        if (algoChoice == 1) {
            algorithm = new SimplePixel(databank, radarImage);
        } else { // algoChoice == 2
            algorithm = new AveragePixel(databank, radarImage);
        }

        // Exécuter l'algorithme pour la date spécifiée
        algorithm->getDataForDay(date);

        // Libérer la mémoire
        delete algorithm;
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de l'exécution: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}