#include "Databank.h"
#include "Station.h"
#include "Date.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>
#include "Station.h"
#include "Date.h"

// Constructeur
Databank::Databank(const std::string& stationsFile, const std::string& dataFile) {
    loadStations("stations.csv");
    loadData("donnees.csv");
}

// Méthode pour charger les stations depuis le fichier CSV
void Databank::loadStations(const std::string& stationsFile) {
    std::ifstream file(stationsFile);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier de stations: " + stationsFile);
    }

    std::string line;
    // Ignorer la première ligne (en-têtes)
    std::getline(file, line);

    // Lire chaque ligne et créer un objet Station
    while (std::getline(file, line)) {
        try {
            Station station(line);
            stations.push_back(station);
        } catch (const std::exception& e) {
            std::cerr << "Erreur lors du traitement d'une station: " << e.what() << std::endl;
            std::cerr << "Ligne: " << line << std::endl;
        }
    }

    // Trier les stations (optionnel, mais peut être utile)
    std::sort(stations.begin(), stations.end());
}

// Méthode pour charger les données pluviométriques depuis le fichier CSV
void Databank::loadData(const std::string& dataFile) {
    std::ifstream file(dataFile);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier de données: " + dataFile);
    }

    std::string line;
    // Ignorer la première ligne (en-têtes)
    std::getline(file, line);

    // Ensemble des dates pour lesquelles nous avons des images radar
    // Note: Cet ensemble doit être rempli avec les dates pour lesquelles il y a des images radar disponibles
    // Pour ce TP, nous supposons que les dates sont entre le 1er octobre 2024 et le 28 février 2025
    std::set<Date> validDates;
    // Remplir avec les dates valides (à adapter selon les images radar disponibles)
    for (int month = 10; month <= 12; ++month) {
        for (int day = 1; day <= 31; ++day) {
            if ((month == 11 && day > 30) || (month == 2 && day > 29)) continue;
            try {
                validDates.insert(Date(2024, month, day));
            } catch (const std::exception&) {
                // Ignorer les dates invalides
            }
        }
    }
    for (int month = 1; month <= 2; ++month) {
        for (int day = 1; day <= 31; ++day) {
            if (month == 2 && day > 28) continue;
            try {
                validDates.insert(Date(2025, month, day));
            } catch (const std::exception&) {
                // Ignorer les dates invalides
            }
        }
    }

    // Lire chaque ligne du fichier de données
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;

        // Format attendu: NUM_POSTE;DATE;PRECIP_Q (et potentiellement d'autres champs)
        std::string numPoste;
        std::string dateStr;
        std::string precipStr;

        std::getline(ss, numPoste, ';');  // NUM_POSTE
        std::getline(ss, dateStr, ';');   // DATE (format attendu: YYYY-MM-DD)
        std::getline(ss, precipStr, ';'); // PRECIP_Q

        try {
            // Parser la date
            std::stringstream dateSS(dateStr);
            std::string yearStr, monthStr, dayStr;
            std::getline(dateSS, yearStr, '-');
            std::getline(dateSS, monthStr, '-');
            std::getline(dateSS, dayStr);

            int year = std::stoi(yearStr);
            int month = std::stoi(monthStr);
            int day = std::stoi(dayStr);

            Date date(year, month, day);

            // Vérifier si cette date est valide (a une image radar)
            if (validDates.find(date) != validDates.end()) {
                // Parser la pluviométrie
                double precip = std::stod(precipStr);

                // Stocker la donnée
                data[std::make_pair(numPoste, date)] = precip;
            }
        } catch (const std::exception& e) {
            std::cerr << "Erreur lors du traitement d'une donnée: " << e.what() << std::endl;
            std::cerr << "Ligne: " << line << std::endl;
        }
    }
}

// Méthodes pour accéder aux itérateurs du conteneur de stations
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

// Méthode pour obtenir la pluviométrie pour une station et une date données
double Databank::getRainfall(const Station& station, const Date& date) const {
    auto key = std::make_pair(station.getNUM_POSTE(), date);
    auto it = data.find(key);

    if (it != data.end()) {
        return it->second;
    } else {
        return NAN; // Not A Number si la donnée n'est pas disponible
    }
}