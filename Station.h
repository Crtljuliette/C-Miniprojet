#ifndef STATION_H
#define STATION_H

#include <string>
#include <iostream>

class Station {
private:
    std::string numer_sta;
    std::string nom;
    double latitude;
    double longitude;
    double altitude;

public:
    Station(const std::string& csvLine);

    std::string getNumerSta() const;
    std::string getNom() const;
    double getLatitude() const;
    double getLongitude() const;
    double getAltitude() const;

    // Opérateurs de comparaison pour utiliser Station
    bool operator==(const Station& other) const;
    bool operator<(const Station& other) const;
};

#endif
