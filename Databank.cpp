#include "Databank.h"
#include "CsvWhitespace.h"
#include "Station.h"
#include "Date.h"
#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructeur
Databank::Databank(const std::string& stationsFilename, const std::string& dataFilename) {
    loadStations(stationsFilename);
    loadData(dataFilename);
}

// Méthode privée pour charger la liste des stations
void Databank::loadStations(const std::string& stationsFilename) {
    // Ouverture du fichier
    std::ifstream file(stationsFilename);
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier des stations: " << stationsFilename << std::endl;
        return;
    }

    // Application du localisateur pour le parsing des CSV
    file.imbue(std::locale(file.getloc(), new CsvWhitespace));

    // Lecture de l'en-tête (pour l'ignorer)
    std::string header;
    std::getline(file, header);

    // Lecture des stations
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Création de la station à partir de la ligne CSV
        Station station(line);

        // Ajout de la station dans le conteneur, en utilisant insert au lieu de []
        stations.insert(std::make_pair(station.getNUM_POSTE(), station));
    }

    file.close();
}

// Méthode privée pour charger les données des stations
void Databank::loadData(const std::string& dataFilename) {
    // Ouverture du fichier
    std::ifstream file(dataFilename);
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier de données: " << dataFilename << std::endl;
        return;
    }

    // Application du localisateur pour le parsing des CSV
    file.imbue(std::locale(file.getloc(), new CsvWhitespace));

    // Lecture de l'en-tête (pour l'ignorer)
    std::string header;
    std::getline(file, header);

    // Lecture des données
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Utilisation d'un stringstream avec notre localisateur CSV
        std::istringstream iss(line);
        iss.imbue(std::locale(iss.getloc(), new CsvWhitespace));

        // Variables pour stocker les données extraites
        std::string stationId, stationName, latStr, lonStr, altiStr, dateStr, rainfallStr;
        std::string tempMin, tempMax, tempMean; // Autres colonnes présentes dans le fichier

        // Lecture des colonnes selon l'ordre dans le fichier
        // NUM_POSTE;NOM_USUEL;LAT;LON;ALTI;AAAAMMJJ;RR;TN;TX;TM
        iss >> stationId >> stationName >> latStr >> lonStr >> altiStr 
            >> dateStr >> rainfallStr >> tempMin >> tempMax >> tempMean;

        // Vérifier si la station existe dans notre liste
        if (!hasStation(stationId)) {
            continue; // Ignorer les données des stations inconnues
        }

        // Convertir la date (format AAAAMMJJ)
        int year = std::stoi(dateStr.substr(0, 4));
        int month = std::stoi(dateStr.substr(4, 2));
        int day = std::stoi(dateStr.substr(6, 2));

        // Création de l'objet Date
        Date date(year, month, day);

        // Convertir la pluviométrie
        float rainfall = NAN; // Par défaut, non disponible
        try {
            rainfall = std::stof(rainfallStr);
        } catch (const std::exception& e) {
            // En cas d'erreur de conversion, laisser à NAN
        }

        // Utiliser insert_or_assign pour les données de pluviométrie aussi
        auto& dateMap = rainfall_data[stationId]; // On peut toujours utiliser [] ici car la map est de <string, map>
        dateMap.insert_or_assign(date, rainfall);
    }

    file.close();
}

// Méthodes pour itérer sur les stations
Databank::iterator Databank::begin() {
    return stations.begin();
}

Databank::iterator Databank::end() {
    return stations.end();
}

Databank::const_iterator Databank::begin() const {
    return stations.begin();
}

Databank::const_iterator Databank::end() const {
    return stations.end();
}

// Accesseur pour récupérer la pluviométrie d'une station à une date donnée
float Databank::getRainfallData(const Station& station, const Date& date) const {
    std::string stationId = station.getNUM_POSTE();

    // Vérifier si la station existe dans nos données
    auto stationIt = rainfall_data.find(stationId);
    if (stationIt == rainfall_data.end()) {
        return NAN; // Station non trouvée
    }

    // Vérifier si la date existe pour cette station
    auto dateIt = stationIt->second.find(date);
    if (dateIt == stationIt->second.end()) {
        return NAN; // Pas de données pour cette date
    }

    // Retourner la valeur de pluviométrie
    return dateIt->second;
}

// Méthode utilitaire pour vérifier si une station existe
bool Databank::hasStation(const std::string& stationId) const {
    return stations.find(stationId) != stations.end();
}

// Accesseur pour obtenir une station par son ID
const Station* Databank::getStationById(const std::string& stationId) const {
    auto it = stations.find(stationId);
    if (it != stations.end()) {
        return &(it->second);
    }
    return nullptr;
}