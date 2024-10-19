#ifndef CELL_FIN_H
#define CELL_FIN_H

#include <string>
#include <vector>
#include <stdexcept>
#include <numeric>
#include <algorithm>

// Абстрактный базовый класс ячейки
class Cell {
public:
    virtual ~Cell() = default;
    virtual std::string identify() const = 0; // Возвращает строковое описание ячейки
};

// Текстовая ячейка
class TextCell : public Cell {
private:
    std::string textValue;

public:
    TextCell(const std::string& text);
    std::string identify() const override;
    std::string getTextValue() const;
};

// Числовая ячейка
class NumericCell : public Cell {
private:
    double numericValue;

public:
    NumericCell(double number);
    std::string identify() const override;
    double getNumericValue() const;
};

// Ячейка с формулой
class FormulaCell : public Cell {
private:
    size_t startRow, startCol, endRow, endCol;
    std::string operation;

public:
    FormulaCell(size_t startRow, size_t startCol, size_t endRow, size_t endCol, const std::string& op);
    std::string identify() const override;
    double calculate(const std::vector<std::vector<Cell*>>& table) const;
};

#endif
