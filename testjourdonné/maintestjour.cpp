#include <iostream>
#include "Date.h"
#include "Ressources-20250407/RadarImage.h"
#include "DATABANK/Databank.h"

/*
int main(){
  Databank db("STATION/stations.csv","donnees.csv");
  RadarImage radar("radar/2024-11-20.tif");
  Date date(2024,11,20);

  for (auto it = db.begin(); it != db.end(); ++it)
    Station station = *it;
    float rain_station = db.getRainfall(station,date);
    float rain_radar = radar.getRainfallAtCoordinates(station.getLatitude(),station.getLongitude());

   std::cout << "Station: " << station.getName() << ", Rainfall (Station): " << rain_station << " mm, Rainfall (Radar): " << rain_radar << " mm" << std::endl;
  }

  return 0;  
 
}