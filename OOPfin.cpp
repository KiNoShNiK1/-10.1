#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <stdexcept>
#include <numeric>
#include <algorithm> // для std::min, std::max

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
    TextCell(const std::string& text) : textValue(text) {}

    std::string identify() const override {
        return "Текстовая ячейка: " + textValue;
    }

    std::string getTextValue() const {
        return textValue;
    }
};

// Числовая ячейка
class NumericCell : public Cell {
private:
    double numericValue;

public:
    NumericCell(double number) : numericValue(number) {}

    std::string identify() const override {
        return "Числовая ячейка: " + std::to_string(numericValue);
    }

    double getNumericValue() const {
        return numericValue;
    }
};

// Ячейка с формулой
class FormulaCell : public Cell {
private:
    size_t startRow, startCol, endRow, endCol;
    std::string operation;

public:
    FormulaCell(size_t startRow, size_t startCol, size_t endRow, size_t endCol, const std::string& op)
        : startRow(startRow), startCol(startCol), endRow(endRow), endCol(endCol), operation(op) {}

    std::string identify() const override {
        return "Ячейка с формулой: " + operation + " от (" +
               std::to_string(startRow) + ", " + std::to_string(startCol) + ") до (" +
               std::to_string(endRow) + ", " + std::to_string(endCol) + ")";
    }

    double calculate(const std::vector<std::vector<Cell*>>& table) const {
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
};

// Таблица, содержащая ячейки
class Table {
private:
    std::vector<std::vector<Cell*>> cells;

public:
    Table(size_t rows, size_t cols)
        : cells(rows, std::vector<Cell*>(cols, nullptr)) {}

    ~Table() { clearTable(); }

    size_t getRows() const { return cells.size(); }

    size_t getCols() const { return cells.empty() ? 0 : cells[0].size(); }

    // Получение ячейки
    Cell* getCell(size_t row, size_t col) const {
        assert(row < cells.size() && col < cells[0].size());
        return cells[row][col];
    }

    // Установка ячейки
    void setCell(size_t row, size_t col, Cell* cell) {
        assert(row < cells.size() && col < cells[0].size());
        delete cells[row][col];
        cells[row][col] = cell;
    }

    // Очистка ячейки
    void clearCell(size_t row, size_t col) {
        assert(row < cells.size() && col < cells[0].size());
        delete cells[row][col];
        cells[row][col] = nullptr;
    }

    // Очистка всей таблицы
    void clearTable() {
       for (auto& row : cells) {
           for (auto& cell : row) {
               delete cell;
               cell = nullptr;
           }
       }
   }

    // Проверка и вывод всех ячеек
    void checkCells() const {
       for (size_t i = 0; i < getRows(); ++i) {
           for (size_t j = 0; j < getCols(); ++j) {
               if (cells[i][j]) {
                   std::cout << cells[i][j]->identify() << std::endl;
               } else {
                   std::cout << "Ячейка (" << i << ", " << j << ") пустая." << std::endl;
               }
           }
       }
    }

    // Изменение размера таблицы
    void resize(size_t newRows, size_t newCols) {
       // Изменение размера таблицы
       cells.resize(newRows);
       for (auto& row : cells) {
           row.resize(newCols, nullptr);
       }
   }

    const std::vector<std::vector<Cell*>>& getCells() const {
       return cells;
    }
};

int main() {
   Table table(3, 3);
   assert(table.getRows() == 3);
   assert(table.getCols() == 3);

   table.setCell(0, 0, new TextCell("Hello"));
   table.setCell(1, 1, new NumericCell(42.0));
   table.setCell(2, 2, new TextCell("World"));

   table.setCell(0, 1, new FormulaCell(1, 1, 1, 1, "sum"));
   table.setCell(1, 2, new NumericCell(58.0));
   table.setCell(2, 1, new FormulaCell(1, 1, 2, 2, "average"));
   table.setCell(0, 2, new FormulaCell(1, 1, 2, 2, "max"));

   table.checkCells();

   try {
       auto formulaSum = dynamic_cast<FormulaCell*>(table.getCell(0, 1));
       if (formulaSum) {
           double resultSum = formulaSum->calculate(table.getCells());
           std::cout << "Результат суммы: " << resultSum << std::endl;
       }

       auto formulaAvg = dynamic_cast<FormulaCell*>(table.getCell(2, 1));
       if (formulaAvg) {
           double resultAvg = formulaAvg->calculate(table.getCells());
           std::cout << "Результат среднего: " << resultAvg << std::endl;
       }

       auto formulaMax = dynamic_cast<FormulaCell*>(table.getCell(0, 2));
       if (formulaMax) {
           double resultMax = formulaMax->calculate(table.getCells());
           std::cout << "Максимальное значение: " << resultMax << std::endl;
       }

   } catch (const std::exception& e) {
       std::cout << e.what() << std::endl;
   }

   table.clearCell(1, 1);
   table.checkCells();

   table.clearTable();
   table.checkCells();

   return 0;
}
