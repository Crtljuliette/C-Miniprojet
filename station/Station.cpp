//numer_sta : identifiant unique de la station
//nom : nom de la station
//latitude / longitude : localisation géographique
//altitude : en mètres

#include <iostream>
#include <string>
#include "Station.h"
#include <sstream>

Station::Station(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string field;

    std::getline(ss, numer_sta, ';');   // idd station
    std::getline(ss, nom, ';');         // nom station
    std::getline(ss, field, ';');       // latitude
    latitude = std::stod(field);
    std::getline(ss, field, ';');       // longitude
    longitude = std::stod(field);
    std::getline(ss, field, ';');       // altitude
    altitude = std::stod(field);
}

std::string Station::getNumerSta() const {
    return numer_sta;
}

std::string Station::getNom() const {
    return nom;
}

double Station::getLatitude() const {
    return latitude;
}

double Station::getLongitude() const {
    return longitude;
}

double Station::getAltitude() const {
    return altitude;
}

bool Station::operator==(const Station& other) const {
    return numer_sta == other.numer_sta;
}

bool Station::operator<(const Station& other) const {
    return numer_sta < other.numer_sta;
}
