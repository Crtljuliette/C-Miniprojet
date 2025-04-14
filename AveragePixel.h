#ifndef AVERAGE_PIXEL_H
#define AVERAGE_PIXEL_H

#include "ComparisonAlgorithm.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

class AveragePixel : public ComparisonAlgorithm {
public:
    // Constructeur utilisant celui de la classe parent
    AveragePixel(Databank& db, RadarImage& radar) : ComparisonAlgorithm(db, radar) {}

    // Implémentation de la méthode virtuelle directement dans l'en-tête
    void getDataForDay(const Date& date) override {
        // Itérer sur toutes les stations de la banque de données
        for (auto it = databank.begin(); it != databank.end(); ++it) {
            const Station& station = it->second;

            // Obtenir la pluviométrie de la station pour cette date
            float stationRainfall = databank.getRainfallData(station, date);

            // Obtenir la pluviométrie moyenne du radar (9 pixels) à la position de la station
            float radarRainfall = getAverageRainfallAtCoordinates(
                station.getLAT(), station.getLON());

            // Afficher les informations de comparaison
            std::cout << station.getNUM_POSTE() << ","
                      << station.getNOM_USUEL() << ","
                      << std::fixed << std::setprecision(1) << stationRainfall << ","
                      << radarRainfall << std::endl;
        }
    }

private:
    // Méthode auxiliaire pour calculer la moyenne des 9 pixels environnants
    float getAverageRainfallAtCoordinates(float lat, float lon) {
        // Calculer la distance approximative en degrés correspondant à un pixel
        const float latStep = (radarImage.getMaxLatitude() - radarImage.getMinLatitude()) / radarImage.getHeight();
        const float lonStep = (radarImage.getMaxLongitude() - radarImage.getMinLongitude()) / radarImage.getWidth();

        // Calculer les indices de ligne et colonne du pixel central
        float latRange = radarImage.getMaxLatitude() - radarImage.getMinLatitude();
        int centerRow = static_cast<int>((radarImage.getMaxLatitude() - lat) / latRange * radarImage.getHeight());

        float lonRange = radarImage.getMaxLongitude() - radarImage.getMinLongitude();
        int centerCol = static_cast<int>((lon - radarImage.getMinLongitude()) / lonRange * radarImage.getWidth());

        // S'assurer que les indices sont dans les limites
        centerRow = std::max(0, std::min(centerRow, radarImage.getHeight() - 1));
        centerCol = std::max(0, std::min(centerCol, radarImage.getWidth() - 1));

        float totalRainfall = 0.0f;
        int validPixelCount = 0;

        // Parcourir les 9 pixels (3x3 autour du point central)
        for (int dRow = -1; dRow <= 1; ++dRow) {
            for (int dCol = -1; dCol <= 1; ++dCol) {
                int row = centerRow + dRow;
                int col = centerCol + dCol;

                // Vérifier si les indices sont dans les limites
                if (row >= 0 && row < radarImage.getHeight() && 
                    col >= 0 && col < radarImage.getWidth()) {

                    // Obtenir la valeur du pixel
                    uint16_t rawData = radarImage.getDataAtPixel(row, col);
                    float pixelRainfall = rawData * RadarImage::getConversionFactor();

                    totalRainfall += pixelRainfall;
                    validPixelCount++;
                }
            }
        }

        // Retourner la moyenne ou 0 si aucun pixel valide
        return (validPixelCount > 0) ? (totalRainfall / validPixelCount) : 0.0f;
    }
};

#endif // AVERAGE_PIXEL_H