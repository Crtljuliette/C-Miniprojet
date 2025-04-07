#include "Station.h"
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream file("stations.csv");
    std::string line;

    
    std::getline(file, line);

    std::vector<Station> stations;

    while (std::getline(file, line)) {
        Station s(line);
        stations.push_back(s);
    }

    for (const auto& s : stations) {
        std::cout << s.getNumerSta() << " - " << s.getNom()
                  << " (" << s.getLatitude() << ", "
                  << s.getLongitude() << ") Alt: "
                  << s.getAltitude() << "m" << std::endl;
    }

    return 0;
}
