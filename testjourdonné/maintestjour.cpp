
#include <iostream>
#include <iomanip>
#include "Date.h"
#include "Databank.h"
#include "RadarImage.h"
/*
int main() {
    Date date(2024, 11, 20);

    Databank db("stations.csv", "donnees.csv");
    RadarImage radar("radar/2024-11-02.tif");

    std::cout << "id_station,nom_station,pluie_station,pluie_radar\n";

    for (auto it = db.begin(); it != db.end(); ++it) {
        const Station& station = it->second;
        float stationRain = db.getRainfallData(station, date);
        float radarRain = radar.getRainfallAtCoordinates(station.getLAT(), station.getLON());

        std::cout << station.getNUM_POSTE() << ","
                  << station.getNOM_USUEL() << ","
                  << std::fixed << std::setprecision(2)
                  << stationRain << ","
                  << radarRain << "\n";
    }

    return 0;
}

/*/