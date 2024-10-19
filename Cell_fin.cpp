#include "Cell_fin.h"

// Реализация методов TextCell
TextCell::TextCell(const std::string& text) : textValue(text) {}

std::string TextCell::identify() const {
    return "Текстовая ячейка: " + textValue;
}

std::string TextCell::getTextValue() const {
    return textValue;
}

// Реализация методов NumericCell
NumericCell::NumericCell(double number) : numericValue(number) {}

std::string NumericCell::identify() const {
    return "Числовая ячейка: " + std::to_string(numericValue);
}

double NumericCell::getNumericValue() const {
    return numericValue;
}

// Реализация методов FormulaCell
FormulaCell::FormulaCell(size_t startRow, size_t startCol, size_t endRow, size_t endCol, const std::string& op)
    : startRow(startRow), startCol(startCol), endRow(endRow), endCol(endCol), operation(op) {}

std::string FormulaCell::identify() const {
    return "Ячейка с формулой: " + operation + " от (" +
           std::to_string(startRow) + ", " + std::to_string(startCol) + ") до (" +
           std::to_string(endRow) + ", " + std::to_string(endCol) + ")";
}

double FormulaCell::calculate(const std::vector<std::vector<Cell*>>& table) const {
    std::vector<double> values;

    for (size_t i = startRow; i <= endRow; ++i) {
        for (size_t j = startCol; j <= endCol; ++j) {
            if (auto numericCell = dynamic_cast<NumericCell*>(table[i][j])) {
                values.push_back(numericCell->getNumericValue());
            } else {
                throw std::runtime_error("Ошибка: не все ячейки числовые.");
            }
        }
    }

    if (values.empty()) {
        throw std::runtime_error("Ошибка: диапазон ячеек пустой.");
    }

    if (operation == "sum") {
        return std::accumulate(values.begin(), values.end(), 0.0);
    } else if (operation == "product") {
        return std::accumulate(values.begin(), values.end(), 1.0, std::multiplies<double>());
    } else if (operation == "average") {
        return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
    } else if (operation == "max") {
        return *std::max_element(values.begin(), values.end());
    } else if (operation == "min") {
        return *std::min_element(values.begin(), values.end());
    } else {
        throw std::runtime_error("Ошибка: операция '" + operation + "' не поддерживается.");
    }
}
