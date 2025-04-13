#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
    // Attributs de la classe Date
    int year;
    int month;
    int day;
public:
    static bool isValid(int y, int m, int d) ;
    // Constructeurs
    Date(); // Initialise au 1er octobre 2024
    Date(int y, int m, int d);

    // Accesseurs
    int getYear() const;
    int getMonth() const;
    int getDay() const;

    // Modificateurs
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);

    // Opérateurs arithmétiques
    Date& operator+=(int days);
    Date operator+(int days) const;
    Date& operator++(); // Préfixe ++date

    // Opérateurs de comparaison (pour utilisation comme clé)
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;

    // Opérateur d'affichage
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

#endif // DATE_H