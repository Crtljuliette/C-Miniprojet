#include "DATABANK/Databank.h"
#include "DATE/Date.h"
#include "STATION/Station.h"
#include <iostream>
#include <iomanip>


int main() {
    try {
        // Charger la banque de données
        std::cout << "Chargement des données..." << std::endl;
        Databank Databank("stations.csv", "donnees.csv");
        std::cout << "Données chargées avec succès." << std::endl;

        // Afficher toutes les stations
        std::cout << "\nListe des stations:" << std::endl;
        std::cout << std::setw(15) << "NUM_POSTE" << std::setw(25) << "NOM_USUEL" 
                  << std::setw(10) << "LAT" << std::setw(10) << "LON" << std::setw(10) << "ALTI" << std::endl;
        std::cout << std::string(70, '-') << std::endl;

        for (const auto& station : Databank) {
            std::cout << std::setw(15) << station.getNUM_POSTE() 
                      << std::setw(25) << station.getNOM_USUEL()
                      << std::setw(10) << std::fixed << std::setprecision(4) << station.getLAT()
                      << std::setw(10) << std::fixed << std::setprecision(4) << station.getLON()
                      << std::setw(10) << std::fixed << std::setprecision(1) << station.getALTI() << std::endl;
        }

        // Test de récupération des données de pluie pour quelques dates et stations
        std::cout << "\nTest de récupération des données de pluie:" << std::endl;

        // Supposons que nous avons quelques stations et dates connues
        if (Databank.begin() != Databank.end()) {
            Station firstStation = *Databank.begin();
            Date testDate(2024, 10, 15);  // Une date dans la période valide

            double rainfall = Databank.getRainfall(firstStation, testDate);
            std::cout << "Pluviométrie pour la station " << firstStation.getNOM_USUEL() 
                      << " le " << testDate << ": ";

            if (std::isnan(rainfall)) {
                std::cout << "Pas de données disponibles" << std::endl;
            } else {
                std::cout << rainfall << " mm" << std::endl;
            }
        } else {
            std::cout << "Aucune station disponible pour tester les données de pluie." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
