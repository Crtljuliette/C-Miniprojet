#ifndef STATION_H
#define STATION_H

#include <string>
#include <iostream>

class Station {
private:
    std::string NUM_POSTE;
    std::string NOM_USUEL;
    double LAT;
    double LON;
    double ALTI;

public:
    Station(const std::string& csvLine);

    std::string getNUM_POSTE() const;
    std::string getNOM_USUEL() const;
    double getLAT() const;
    double getLON() const;
    double getALTI() const;

    // Opérateurs de comparaison pour utiliser Station
    bool operator==(const Station& other) const;
    bool operator<(const Station& other) const;
};

#endif
