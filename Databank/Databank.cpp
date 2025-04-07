#include "Databank/Databank.h"
#include <fstream>
#include <sstream>
#include <iostream>

Databank::Databank(const std::string& stationsFile, const std::string& dataFile) {
    loadStations(station/stations.csv);
    loadData(donnees.csv)
        ;
}

Databank::StationIterator Databank::begin() {
    return stations.begin();
}

Databank::StationIterator Databank::end() {
    return stations.end();
}

double Databank::getRainfall(const Station& station, const Date& date) const {
    auto stationIt = data.find(station.getNumerSta());
    if (stationIt != data.end()) {
        auto dateIt = stationIt->second.find(date);
        if (dateIt != stationIt->second.end()) {
            return dateIt->second;
        }
    }
    return std::nan("1");
}

void Databank::loadStations(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        stations.emplace_back(line);
    }
}

void Databank::loadData(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string stationIdStr, dateStr;
        double rainfall;
        if (std::getline(ss, stationIdStr, ',') && std::getline(ss, dateStr, ',') && ss >> rainfall) {
            std::istringstream dateSS(dateStr);
            int year, month, day;
            char delim;
            if (dateSS >> year >> delim >> month >> delim >> day) {
                Date date(year, month, day);
                data[stationIdStr][date] = rainfall;
            }
        }
    }
}
