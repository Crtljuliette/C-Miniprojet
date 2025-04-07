#ifndef DATABANK_H
#define DATABANK_H

#include "DATE/Date.h"
#include "station/Station.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>

class Databank {
public:
    using StationIterator = std::vector<Station>::iterator;

    Databank(const std::string& stationsFile, const std::string& dataFile);

    StationIterator begin();
    StationIterator end();

    double getRainfall(const Station& station, const Date& date) const;

private:
    void loadStations(const std::string& filename);
    void loadData(const std::string& filename);

    std::vector<Station> stations;
    std::unordered_map<std::string, std::unordered_map<Date, double>> data;
};

#endif // DATABANK_H
