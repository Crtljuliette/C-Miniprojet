#ifndef DATABANK_H
#define DATABANK_H

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include "DATE/Date.h"
#include "STATION/Station.h"

class Databank {
private:
    // Conteneur pour stocker les stations
    std::vector<Station> stations;

    // Conteneur pour stocker les données pluviométriques indexées par station et par date
    // Utilisation d'une map avec une paire (NUM_POSTE, Date) comme clé et la valeur pluviométrique comme valeur
    std::map<std::pair<std::string, Date>, double> data;

    // Méthodes privées pour charger les données
    void loadStations(const std::string& stationsFile);
    void loadData(const std::string& dataFile);

public:
    // Alias de type pour les itérateurs
    using iterator = std::vector<Station>::iterator;
    using const_iterator = std::vector<Station>::const_iterator;

    // Constructeur
    Databank(const std::string& stationsFile, const std::string& dataFile);

    // Méthodes pour accéder aux itérateurs du conteneur de stations
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // Méthode pour obtenir la pluviométrie pour une station et une date données
    float getRainfall(int Station, const std::string& date);
};

#endif // DATABANK_H