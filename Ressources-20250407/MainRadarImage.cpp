#include <iostream>
#include "Ressources-20250407/RadarImage.h"
/*
int main() {
    const std::string filename = "radar/2024-11-02.tif";
    RadarImage radar(filename);

    // Vérification de la validité de l'image radar
    if (!radar.isValid()) {
        std::cerr << "Erreur dans le chargement de l'image: " << filename << std::endl;
        return 1;
    }

    std::cout << "Image lue correctement." << std::endl;
    std::cout << "Largeur: " << radar.getWidth() << ", Longeur: " << radar.getHeight() << std::endl;
    std::cout << "Bornes Géographiques: " << std::endl;
    std::cout << "  Latitude: " << radar.getMinLatitude() << " à " << radar.getMaxLatitude() << std::endl;
    std::cout << "  Longitude: " << radar.getMinLongitude() << " à " << radar.getMaxLongitude() << std::endl;

    // Test de coordonnées spécifiques
    const float testLat1 = 48.8566; // Paris latitude
    const float testLon1 = -2.3522; // Paris longitude 

    const float testLat2 = 47.2184; // Nantes latitude
    const float testLon2 = -1.5536; // Nantes longitude

    // Test milieu de l'image
    const float testLat3 = (radar.getMinLatitude() + radar.getMaxLatitude()) / 2.0f;
    const float testLon3 = (radar.getMinLongitude() + radar.getMaxLongitude()) / 2.0f;

    std::cout << "\nTest de Rainfall à certaines coordonnées:" << std::endl;

    std::cout << "Paris (" << testLat1 << ", " << testLon1 << "): " 
              << radar.getRainfallAtCoordinates(testLat1, testLon1) << " mm/h" << std::endl;

    std::cout << "Nantes (" << testLat2 << ", " << testLon2 << "): " 
              << radar.getRainfallAtCoordinates(testLat2, testLon2) << " mm/h" << std::endl;

    std::cout << "Center (" << testLat3 << ", " << testLon3 << "): " 
              << radar.getRainfallAtCoordinates(testLat3, testLon3) << " mm/h" << std::endl;

    // Test des valeurs brutes des pixels
    const int centerRow = radar.getHeight() / 2;
    const int centerCol = radar.getWidth() / 2;

    std::cout << "\nValeur Pixel brute au centre (" << centerRow << ", " << centerCol << "): " 
              << radar.getDataAtPixel(centerRow, centerCol) << std::endl;

    // Test des coordonnées hors-limites
    std::cout << "\nTest des coordonnées hors-limites:" << std::endl;
    const float outOfBoundsLat = radar.getMaxLatitude() + 1.0f;
    const float outOfBoundsLon = radar.getMaxLongitude() + 1.0f;

    std::cout << "Hors-Limites (" << outOfBoundsLat << ", " << outOfBoundsLon << "): " 
              << radar.getRainfallAtCoordinates(outOfBoundsLat, outOfBoundsLon) << " mm/h" << std::endl;

    return 0;
}
/*/