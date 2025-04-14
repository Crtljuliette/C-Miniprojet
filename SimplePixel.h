#ifndef SIMPLE_PIXEL_H
#define SIMPLE_PIXEL_H

#include "ComparisonAlgorithm.h"
#include <iostream>
#include <iomanip>

class SimplePixel : public ComparisonAlgorithm {
public:
    // Constructeur utilisant celui de la classe parent
    SimplePixel(Databank& db, RadarImage& radar) : ComparisonAlgorithm(db, radar) {}

    // Implémentation de la méthode virtuelle directement dans l'en-tête
    void getDataForDay(const Date& date) override {
        // Itérer sur toutes les stations de la banque de données
        for (auto it = databank.begin(); it != databank.end(); ++it) {
            const Station& station = it->second;

            // Obtenir la pluviométrie de la station pour cette date
            float stationRainfall = databank.getRainfallData(station, date);

            // Obtenir la pluviométrie du radar à la position de la station
            float radarRainfall = radarImage.getRainfallAtCoordinates(
                station.getLAT(), station.getLON());

            // Afficher les informations de comparaison
            std::cout << station.getNUM_POSTE() << ","
                      << station.getNOM_USUEL() << ","
                      << std::fixed << std::setprecision(1) << stationRainfall << ","
                      << radarRainfall << std::endl;
        }
    }
};

#endif // SIMPLE_PIXEL_H