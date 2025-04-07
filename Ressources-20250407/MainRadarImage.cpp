#include <iostream>
#include "Ressources-20250407/RadarImage.h"
#include "Ressources-20250407/RadarImage.cpp"
#include "radar/2024-11-02.tif"
<<<<<<< HEAD
/*/
=======
#include "Ressources-20250407/tinytiff/tinytiff.h"
#include "Ressources-20250407/tinytiff/tinytiffreader.h"
#include "Ressources-20250407/tinytiff/tinytiffwriter.h"
#include "Ressources-20250407/tinytiff/tinytiff_ctools.h"
#include "Ressources-20250407/tinytiff/tinytiff_ctools_internal.h"
#include "Ressources-20250407/tinytiff/tiff_definitions_internal.h"

>>>>>>> 0791183 (main)
int main() {
    
    const std::string filename = "radar/2024-11-02.tif";


    RadarImage radar(filename);

    // Vérification de la validité de l'image radar
    if (!radar.isValid()) {
        std::cerr << "Failed to load radar image: " << filename << std::endl;
        return 1;
    }

    std::cout << "Radar image loaded successfully." << std::endl;
    std::cout << "Width: " << radar.getWidth() << ", Height: " << radar.getHeight() << std::endl;
    const int testRows[] = {0, 10, radar.getHeight()/2, radar.getHeight()-1};
    const int testCols[] = {0, 10, radar.getWidth()/2, radar.getWidth()-1};

    for (int row : testRows) {
          for (int col : testCols) {
                    uint16_t value = radar.getDataAtPixel(row, col);
                    std::cout << "Pixel at (" << row << ", " << col << "): " 
                              << value << " (Rainfall: " << value * 0.01 << " mm/h)" << std::endl;
          }
    }

    return 0;
}
    std::cout << "Geographic bounds: " << std::endl;
    std::cout << "  Latitude: " << radar.getMinLatitude() << " to " << radar.getMaxLatitude() << std::endl;
    std::cout << "  Longitude: " << radar.getMinLongitude() << " to " << radar.getMaxLongitude() << std::endl;

    // Test de coordonnées spécifiques
    const float testLat1 = 48.8566; // Paris latitude
    const float testLon1 = -2.3522; // Paris longitude 

    const float testLat2 = 47.2184; // Nantes latitude
    const float testLon2 = -1.5536; // Nantes longitude

    // Test milieu de l'image
    const float testLat3 = (radar.getMinLatitude() + radar.getMaxLatitude()) / 2.0f;
    const float testLon3 = (radar.getMinLongitude() + radar.getMaxLongitude()) / 2.0f;

    std::cout << "\nTesting rainfall at coordinates:" << std::endl;

    std::cout << "Paris (" << testLat1 << ", " << testLon1 << "): " 
              << radar.getRainfallAtCoordinates(testLat1, testLon1) << " mm/h" << std::endl;

    std::cout << "Nantes (" << testLat2 << ", " << testLon2 << "): " 
              << radar.getRainfallAtCoordinates(testLat2, testLon2) << " mm/h" << std::endl;

    std::cout << "Center (" << testLat3 << ", " << testLon3 << "): " 
              << radar.getRainfallAtCoordinates(testLat3, testLon3) << " mm/h" << std::endl;

    // Test des valeurs brutes des pixels
    const int centerRow = radar.getHeight() / 2;
    const int centerCol = radar.getWidth() / 2;

    std::cout << "\nRaw pixel value at center (" << centerRow << ", " << centerCol << "): " 
              << radar.getDataAtPixel(centerRow, centerCol) << std::endl;

    // Test des coordonnées hors-limites
    std::cout << "\nTesting out of bounds coordinates:" << std::endl;
    const float outOfBoundsLat = radar.getMaxLatitude() + 1.0f;
    const float outOfBoundsLon = radar.getMaxLongitude() + 1.0f;

    std::cout << "Out of bounds (" << outOfBoundsLat << ", " << outOfBoundsLon << "): " 
              << radar.getRainfallAtCoordinates(outOfBoundsLat, outOfBoundsLon) << " mm/h" << std::endl;

    return 0;
}
/*/