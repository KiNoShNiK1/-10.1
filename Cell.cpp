#include "Cell.h"

Cell::Cell() : isNumeric(false), isEmpty(true) {}

Cell::Cell(const std::string& text) : textValue(text), isNumeric(false), isEmpty(false) {}

Cell::Cell(double number) : numericValue(number), isNumeric(true), isEmpty(false) {}

Cell::Cell(const Cell& other)
    : textValue(other.textValue), numericValue(other.numericValue),
      isNumeric(other.isNumeric), isEmpty(other.isEmpty) {}

std::string Cell::getTextValue() const {
    return isNumeric || isEmpty ? "" : textValue;
}

double Cell::getNumericValue() const {
    return isNumeric && !isEmpty ? numericValue : 0.0;
}

bool Cell::isNumericCell() const { return isNumeric; }
bool Cell::isEmptyCell() const { return isEmpty; }

void Cell::setTextValue(const std::string& text) {
    textValue = text;
    isNumeric = false;
    isEmpty = false;
}

void Cell::setNumericValue(double number) {
    numericValue = number;
    isNumeric = true;
    isEmpty = false;
}

void Cell::clear() {
    textValue.clear();
    numericValue = 0.0;
    isNumeric = false;
    isEmpty = true;
}
