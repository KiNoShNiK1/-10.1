#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <stdexcept>
#include <numeric>

class Cell {
public:
    virtual ~Cell() = default; 
    virtual std::string identify() const = 0; 
};

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
};

class Table {
private:
    std::vector<std::vector<Cell*>> cells;

public:
    Table(size_t rows, size_t cols) : cells(rows, std::vector<Cell*>(cols, nullptr)) {}
    
    ~Table() {
        for (auto& row : cells) {
            for (auto& cell : row) {
                delete cell; 
            }
        }
    }

    size_t getRows() const { return cells.size(); }
    
    size_t getCols() const { return cells.empty() ? 0 : cells[0].size(); }

    Cell* getCell(size_t row, size_t col) const {
        assert(row < cells.size() && col < cells[0].size());
        return cells[row][col];
    }

    void setCell(size_t row, size_t col, Cell* cell) {
        assert(row < cells.size() && col < cells[0].size());
        delete cells[row][col]; 
        cells[row][col] = cell;
    }

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

   table.checkCells(); 

   try {
       auto formulaCell = dynamic_cast<FormulaCell*>(table.getCell(0, 1));
       if (formulaCell) {
           double result = formulaCell->calculate(table.getCells());
           std::cout << "Результат формулы: " << result << std::endl;
       }
   } catch (const std::exception& e) {
       std::cout << e.what() << std::endl;
   }

   return 0;
}
