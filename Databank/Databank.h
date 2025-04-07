#include "Databank/Databank.h"
#include "DATE/Date.h"
#include <iostream>

int main() {
    Databank databank("stations.csv", "data.csv");

    std::cout << "Stations disponibles :\n";
    for (auto it = databank.begin(); it != databank.end(); ++it) {
        std::cout << "ID: " << it->getNumerSta() << ", Nom: " << it->getNom() << "\n";
    }

    // Exemple d'utilisation pour obtenir la pluviométrie
    Station station("07007,Paris-Montsouris,48.8167,2.3333,75.0");
    Date date(2023, 10, 1);
    double rainfall = databank.getRainfall(station, date);
    if (!std::isnan(rainfall)) {
        std::cout << "Pluviométrie pour " << station.getNom() << " le " << date.getDay() << "/"
                  << date.getMonth() << "/" << date.getYear() << " : " << rainfall << " mm\n";
    } else {
        std::cout << "Aucune donnée disponible pour cette station et cette date.\n";
    }

    return 0;
}