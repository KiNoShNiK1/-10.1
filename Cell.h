#ifndef CELL_H
#define CELL_H

#include <string>

class Cell {
private:
    std::string textValue;
    double numVal;
    bool isNumeric;
    bool isEmpty;

public:
    // Конструкторы
    Cell();
    Cell(const std::string& text);
    Cell(double number);
    Cell(const Cell& other);

    // Методы доступа
    std::string getTextValue() const;
    double getNumericValue() const;
    bool isNumericCell() const;
    bool isEmptyCell() const;

    // Методы изменения состояния
    void setTextValue(const std::string& text);
    void setNumericValue(double number);
    void clear();
};

#endif // CELL_H
