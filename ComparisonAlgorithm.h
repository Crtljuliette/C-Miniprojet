#ifndef COMPARISON_ALGORITHM_H
#define COMPARISON_ALGORITHM_H

#include "Date.h"
#include "Databank.h"
#include "RadarImage.h"

class ComparisonAlgorithm {
protected:
    Databank& databank;
    RadarImage& radarImage;

public:
    // Constructeur
    ComparisonAlgorithm(Databank& db, RadarImage& radar) : databank(db), radarImage(radar) {}

    // Destructeur virtuel
    virtual ~ComparisonAlgorithm() = default;

    // Méthode virtuelle pure à implémenter dans les classes dérivées
    virtual void getDataForDay(const Date& date) = 0;
};

#endif // COMPARISON_ALGORITHM_H