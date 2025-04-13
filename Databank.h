#ifndef DATABANK_H
#define DATABANK_H

#include <string>
#include <vector>
#include <map>
#include <cmath> // Pour NAN
#include "Date.h"
#include "Station.h" 
#include "Parser.h"
#include "CsvWhitespace.h"

class Databank {
private:
    // Stockage des stations (par identifiant)
    std::map<std::string, Station> stations;

    // Stockage des données (indexées par station puis par date)
    // Format: map[ID_STATION][DATE] = pluviométrie
    std::map<std::string, std::map<Date, float>> rainfall_data;

    // Méthodes privées pour charger les données
    void loadStations(const std::string& stationsFilename);
    void loadData(const std::string& dataFilename);

public:
    // Type d'itérateur pour parcourir les stations
    using iterator = std::map<std::string, Station>::iterator;
    using const_iterator = std::map<std::string, Station>::const_iterator;

    // Constructeur
    Databank(const std::string& stationsFilename, const std::string& dataFilename);

    // Méthodes pour itérer sur les stations
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // Accesseur pour récupérer la pluviométrie d'une station à une date donnée
    float getRainfallData(const Station& station, const Date& date) const;

    // Méthode utilitaire pour vérifier si une station existe
    bool hasStation(const std::string& stationId) const;

    // Accesseur pour obtenir une station par son ID
    const Station* getStationById(const std::string& stationId) const;
};

#endif // DATABANK_H