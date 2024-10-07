#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class Cell {
private:
    std::string textValue;
    double numVal;
    bool isNumeric;
    bool isEmpty;

public:
    Cell() : isNumeric(false), isEmpty(true) {}
    Cell(const std::string& text) : textValue(text), isNumeric(false), isEmpty(false) {}
    Cell(double number) : numVal(number), isNumeric(true), isEmpty(false) {}
    Cell(const Cell& other)
        : textValue(other.textValue), numVal(other.numVal),
          isNumeric(other.isNumeric), isEmpty(other.isEmpty) {}

    std::string getTextValue() const {
        return isNumeric || isEmpty ? "" : textValue;
    }

    double getNumericValue() const {
        return isNumeric && !isEmpty ? numVal : 0.0;
    }

    bool isNumericCell() const { return isNumeric; }
    bool isEmptyCell() const { return isEmpty; }

    void setTextValue(const std::string& text) {
        textValue = text;
        isNumeric = false;
        isEmpty = false;
    }

    void setNumericValue(double number) {
        numVal = number;
        isNumeric = true;
        isEmpty = false;
    }

    void clear() {
        textValue.clear();
        numVal = 0.0;
        isNumeric = false;
        isEmpty = true;
    }
};

class Table {
private:
    std::vector<std::vector<Cell>> cells;

public:
    Table() {}
    Table(size_t rows, size_t cols) : cells(rows, std::vector<Cell>(cols)) {}
    
    size_t getRows() const { return cells.size(); }
    
    size_t getCols() const {
        return cells.empty() ? 0 : cells[0].size();
    }

    Cell getCell(size_t row, size_t col) const {
        assert(row < cells.size() && col < cells[0].size());
        return cells[row][col];
    }

    void setCell(size_t row, size_t col, const Cell& cell) {
        assert(row < cells.size() && col < cells[0].size());
        cells[row][col] = cell;
    }

    void resize(size_t rows, size_t cols) {
        cells.resize(rows);
        for (auto& row : cells) {
            row.resize(cols);
        }
    }

   void checkCells() const {
       for (size_t i = 0; i < getRows(); ++i) {
           for (size_t j = 0; j < getCols(); ++j) {
               const Cell& cell = getCell(i, j);
               if (cell.isEmptyCell()) {
                   std::cout << "Ячейка (" << i << ", " << j << ") пустая." << std::endl;
               } else if (cell.isNumericCell()) {
                   std::cout << "Ячейка (" << i << ", " << j << ") числовая: " 
                             << cell.getNumericValue() << std::endl;
               } else {
                   std::cout << "Ячейка (" << i << ", " << j << ") текстовая: " 
                             << cell.getTextValue() << std::endl;
               }
           }
       }
   }
};

int main() {
   Table table(2, 2);
   assert(table.getRows() == 2);
   assert(table.getCols() == 2);

   table.resize(3, 3); // размер таблицы

   // Отладочный вывод
   std::cout << "После изменения размера: Строки = " 
             << table.getRows() 
             << ", Столбцы = " 
             << table.getCols() 
             << std::endl;

   // Проверка утверждения
   assert(table.getCols() == 3); //количество столбцов равно 3

   table.checkCells(); // Проверка ячеек

   std::cout << "Все тесты пройдены успешно!" << std::endl;
   return 0;
}
