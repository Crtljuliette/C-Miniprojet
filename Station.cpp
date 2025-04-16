//NUM_POSTE : identifiant unique de la station
//NOM_USUEL : NOM_USUEL de la station
//LAT / LON : localisation géographique
//ALTI : en mètres

#include <iostream>
#include <string>
#include "Station.h"
#include <sstream>

Station::Station(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string field;

    std::getline(ss, NUM_POSTE, ';');   // idd station
    std::getline(ss, NOM_USUEL, ';');     // NOM_USUEL station
    std::getline(ss, field, ';');       // LAT
    LAT = std::stod(field);
    std::getline(ss, field, ';');       // LON
    LON = std::stod(field);
    std::getline(ss, field, ';');       // ALTI
    ALTI = std::stod(field);
}

std::string Station::getNUM_POSTE() const {
    return NUM_POSTE;
}

std::string Station::getNOM_USUEL() const {
    return NOM_USUEL;
}

double Station::getLAT() const {
    return LAT;
}

double Station::getLON() const {
    return LON;
}

double Station::getALTI() const {
    return ALTI;
}

bool Station::operator==(const Station& other) const {
    return NUM_POSTE == other.NUM_POSTE;
}

bool Station::operator<(const Station& other) const {
    return NUM_POSTE < other.NUM_POSTE;
}
