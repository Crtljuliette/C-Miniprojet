#include "Date.h"
#include <stdexcept>

bool Date::isValid(int y, int m, int d) {
    // Vérifier si l'année est valide
    if (y != 2024 && y != 2025) return false;

    // Vérifier si le mois est valide
    if (m < 1 || m > 12) return false;

    // Vérifier si le jour est valide selon le mois
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // 2024 est une année bissextile
    if (y == 2024 && m == 2) daysInMonth[2] = 29;

    if (d < 1 || d > daysInMonth[m]) return false;

    // Vérifier si la date est dans la plage autorisée
    // Date minimale: 01/10/2024
    if (y == 2024 && m < 10) return false;
    // Date maximale: 28/02/2025
    if (y == 2025 && (m > 2 || (m == 2 && d > 28))) return false;

    return true;
}

// Constructeur par défaut
Date::Date() : year(2024), month(10), day(1) {}

// Constructeur avec paramètres
Date::Date(int y, int m, int d) {
    if (!isValid(y, m, d)) {
        throw std::invalid_argument("Date invalide. Doit être entre le 01/10/2024 et le 28/02/2025.");
    }
    year = y;
    month = m;
    day = d;
}

// Accesseurs
int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }

// Modificateurs
void Date::setYear(int y) {
    if (isValid(y, month, day)) {
        year = y;
    } else {
        throw std::invalid_argument("Année invalide. Doit être 2024 ou 2025.");
    }
}

void Date::setMonth(int m) {
    if (isValid(year, m, day)) {
        month = m;
    } else {
        throw std::invalid_argument("Mois invalide pour cette année.");
    }
}

void Date::setDay(int d) {
    if (isValid(year, month, d)) {
        day = d;
    } else {
        throw std::invalid_argument("Jour invalide pour ce mois et cette année.");
    }
}

// Opérateur +=
Date& Date::operator+=(int days) {
    for (int i = 0; i < days; ++i) {
        ++(*this);  // Utilise l'opérateur d'incrémentation
    }
    return *this;
}

// Opérateur d'incrémentation préfixé (++date)
Date& Date::operator++() {
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // 2024 est une année bissextile
    if (year == 2024 && month == 2) daysInMonth[2] = 29;

    // Incrémenter le jour
    day++;

    // Vérifier si nous devons passer au mois suivant
    if (day > daysInMonth[month]) {
        day = 1;
        month++;

        // Vérifier si nous devons passer à l'année suivante
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    // Vérifier si la nouvelle date est valide
    if (!isValid(year, month, day)) {
        throw std::out_of_range("Date résultante hors plage (01/10/2024 - 28/02/2025).");
    }

    return *this;
}

// Opérateur + (date + jours)
Date Date::operator+(int days) const {
    Date result(*this);
    result += days;
    return result;
}

// Opérateur < (pour comparaison)
bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

// Opérateur == (pour égalité)
bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

// Opérateur d'affichage
std::ostream& operator<<(std::ostream& os, const Date& date) {
    // Format: YYYY-MM-DD
    os << date.year << "-";
    if (date.month < 10) os << "0";
    os << date.month << "-";
    if (date.day < 10) os << "0";
    os << date.day;
    return os;
}