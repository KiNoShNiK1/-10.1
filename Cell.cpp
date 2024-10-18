#include "Cell.h"
#include <stdexcept>
#include <numeric>
#include <iostream>

TextCell::TextCell(const std::string& text) : textValue(text) {}

std::string TextCell::identify() const {
    return "Текстовая ячейка: " + textValue;
}

std::string TextCell::getTextValue() const {
    return textValue;
}

NumericCell::NumericCell(double number) : numericValue(number) {}

std::string NumericCell::identify() const {
    return "Числовая ячейка: " + std::to_string(numericValue);
}

double NumericCell::getNumericValue() const {
    return numericValue;
}

FormulaCell::FormulaCell(size_t startRow, size_t startCol, size_t endRow, size_t endCol, const std::string& op)
    : startRow(startRow), startCol(startCol), endRow(endRow), endCol(endCol), operation(op) {}

std::string FormulaCell::identify() const {
    return "Ячейка с формулой: " + operation + " от (" + 
           std::to_string(startRow) + ", " + std::to_string(startCol) + ") до (" +
           std::to_string(endRow) + ", " + std::to_string(endCol) + ")";
}

double FormulaCell::calculate(const std::vector<std::vector<Cell*>>& table) const {
    if (operation == "sum") {
        double sum = 0.0;
        for (size_t i = startRow; i <= endRow; ++i) {
            for (size_t j = startCol; j <= endCol; ++j) {
                if (auto numericCell = dynamic_cast<NumericCell*>(table[i][j])) {
                    sum += numericCell->getNumericValue();
                } else {
                    throw std::runtime_error("Ошибка: не все ячейки числовые.");
                }
            }
        }
        return sum;
    }
    throw std::runtime_error("Ошибка: операция '" + operation + "' не поддерживается.");
}
