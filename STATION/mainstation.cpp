#include "STATION/Station.h"
#include "DATE/Date.h"
#include "STATION/Station.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>  
#include <algorithm>  
/*
int main() {
    std::ifstream file("station/stations.csv");
    std::string line;
    if (!file) {
        std::cerr << "Erreur : impossible d’ouvrir le fichier stations.csv" << std::endl;
        return 1;
    }

    std::getline(file, line);  // Ignorer la première ligne (entêtes)

    std::vector<Station> stations;  // Déclare un vecteur pour stocker les stations

    while (std::getline(file, line)) {
        Station s(line);  // Crée un objet Station à partir de chaque ligne
        stations.push_back(s);  // Ajoute l'objet Station au vecteur
    }

    // Affichage des informations sur chaque station
    for (const auto& s : stations) {
        std::cout << s.getNUM_POSTE() << " - " << s.getNOM_USUEL()
                  << " (" << s.getLAT() << ", "
                  << s.getLON() << ") Alt: "
                  << s.getALTI() << "m" << std::endl;
    }

    return 0;
}

/*/