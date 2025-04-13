#include <iostream>
#include <iomanip>
#include "Databank.h"

// Fonction d'affichage pour les données d'une station
void printStationInfo(const Station& station) {
    std::cout << "Station: " << station.getNUM_POSTE() << " - " << station.getNOM_USUEL() << std::endl;
    std::cout << "  Coordonnées: LAT=" << station.getLAT() 
              << ", LON=" << station.getLON() 
              << ", ALT=" << station.getALTI() << "m" << std::endl;
}

// Fonction pour afficher les données de pluviométrie pour une période
void printRainfallData(const Databank& databank, const Station& station, 
                       const Date& startDate, const Date& endDate, int daysToShow) {
    // Titre avec le nom de la station
    std::cout << "\nDonnées de pluviométrie pour " << station.getNOM_USUEL() 
              << " (" << station.getNUM_POSTE() << "):" << std::endl;

    // En-tête du tableau
    std::cout << std::setw(12) << "Date" << std::setw(15) << "Pluviométrie (mm)" << std::endl;
    std::cout << std::string(27, '-') << std::endl;

    // Date courante pour l'itération
    Date currentDate = startDate;
    int count = 0;

    // Parcourir les dates et afficher les données
    while (!(currentDate == endDate) && count < daysToShow) {
        float rainfall = databank.getRainfallData(station, currentDate);

        // Afficher la date
        std::cout << std::setw(12) << currentDate;

        // Afficher la valeur de pluviométrie ou "N/A" si non disponible
        if (std::isnan(rainfall)) {
            std::cout << std::setw(15) << "N/A" << std::endl;
        } else {
            std::cout << std::setw(15) << std::fixed << std::setprecision(1) << rainfall << std::endl;
        }

        // Passer au jour suivant
        currentDate = currentDate + 1; // Utilisation de l'opérateur +
        count++;
    }
}

int main() {
    try {
        std::cout << "Chargement des données météorologiques..." << std::endl;

        // Création de la banque de données
        // Remplacez ces chemins par les chemins réels de vos fichiers
        Databank databank("stations.csv", "donnees.csv");

        std::cout << "Données chargées avec succès!" << std::endl;

        // Affichage du nombre de stations
        int stationCount = 0;
        for (auto it = databank.begin(); it != databank.end(); ++it) {
            stationCount++;
        }
        std::cout << "Nombre de stations chargées: " << stationCount << std::endl;

        // Exemple 1 : Afficher les détails de quelques stations
        std::cout << "\n== Exemple 1: Détails de quelques stations ==" << std::endl;
        int count = 0;
        for (auto it = databank.begin(); it != databank.end() && count < 3; ++it, ++count) {
            printStationInfo(it->second);
        }

        // Exemple 2 : Rechercher une station spécifique par ID
        std::cout << "\n== Exemple 2: Recherche d'une station spécifique ==" << std::endl;
        std::string searchId = "25005003"; // Remplacez par un ID valide de votre jeu de données
        const Station* foundStation = databank.getStationById(searchId);

        if (foundStation) {
            std::cout << "Station trouvée:" << std::endl;
            printStationInfo(*foundStation);

            // Exemple 3 : Afficher les données de pluviométrie pour cette station
            std::cout << "\n== Exemple 3: Données de pluviométrie ==" << std::endl;

            // Définir la période (par exemple, 1 semaine en octobre 2024)
            Date startDate(2024, 10, 1);
            Date endDate(2024, 10, 31);

            // Afficher les données pour cette période (limité à 10 jours pour l'exemple)
            printRainfallData(databank, *foundStation, startDate, endDate, 10);
        } else {
            std::cout << "Station avec ID " << searchId << " non trouvée." << std::endl;
        }

        // Exemple 4 : Calculer la pluviométrie moyenne sur une période pour une station
        if (foundStation) {
            std::cout << "\n== Exemple 4: Calcul de pluviométrie moyenne ==" << std::endl;

            Date startDate(2024, 10, 1);
            Date endDate(2024, 10, 31);

            float totalRainfall = 0.0f;
            int validDays = 0;

            Date currentDate = startDate;
            while (!(currentDate == endDate)) {
                float rainfall = databank.getRainfallData(*foundStation, currentDate);
                if (!std::isnan(rainfall)) {
                    totalRainfall += rainfall;
                    validDays++;
                }
                currentDate = currentDate + 1;
            }

            if (validDays > 0) {
                float averageRainfall = totalRainfall / validDays;
                std::cout << "Pluviométrie moyenne pour " << foundStation->getNOM_USUEL() 
                          << " en octobre 2024: " << std::fixed << std::setprecision(1) 
                          << averageRainfall << " mm (sur " << validDays << " jours)" << std::endl;
            } else {
                std::cout << "Aucune donnée valide pour cette période." << std::endl;
            }
        }

        // Exemple 5 : Trouver la station avec la pluviométrie maximale sur une journée
        std::cout << "\n== Exemple 5: Station avec pluviométrie maximale ==" << std::endl;
        Date targetDate(2024, 10, 15); // Date spécifique à analyser

        float maxRainfall = -1.0f;
        std::string maxRainfallStationId;

        for (auto stationIt = databank.begin(); stationIt != databank.end(); ++stationIt) {
            float rainfall = databank.getRainfallData(stationIt->second, targetDate);
            if (!std::isnan(rainfall) && rainfall > maxRainfall) {
                maxRainfall = rainfall;
                maxRainfallStationId = stationIt->first;
            }
        }

        if (!maxRainfallStationId.empty()) {
            const Station* maxStation = databank.getStationById(maxRainfallStationId);
            std::cout << "Le " << targetDate << ", la station avec le plus de précipitations était:" << std::endl;
            printStationInfo(*maxStation);
            std::cout << "Pluviométrie enregistrée: " << std::fixed << std::setprecision(1) 
                      << maxRainfall << " mm" << std::endl;
        } else {
            std::cout << "Aucune donnée de pluviométrie disponible pour le " << targetDate << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}