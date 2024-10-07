#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class Cell {
private:
    std::string textValue;
    double numericValue;
    bool isNumeric;
    bool isEmpty;

public:
    Cell() : isNumeric(false), isEmpty(true) {}
    Cell(const std::string& text) : textValue(text), isNumeric(false), isEmpty(false) {}
    Cell(double number) : numericValue(number), isNumeric(true), isEmpty(false) {}
    Cell(const Cell& other)
        : textValue(other.textValue), numericValue(other.numericValue),
          isNumeric(other.isNumeric), isEmpty(other.isEmpty) {}

    std::string getTextValue() const {
        return isNumeric || isEmpty ? "" : textValue;
    }

    double getNumericValue() const {
        return isNumeric && !isEmpty ? numericValue : 0.0;
    }

    bool isNumericCell() const { return isNumeric; }
    bool isEmptyCell() const { return isEmpty; }

    void setTextValue(const std::string& text) {
        textValue = text;
        isNumeric = false;
        isEmpty = false;
    }

    void setNumericValue(double number) {
        numericValue = number;
        isNumeric = true;
        isEmpty = false;
    }

    void clear() {
        textValue.clear();
        numericValue = 0.0;
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

   // Изменяем размер таблицы
   table.resize(3, 3);

   // Отладочный вывод
   std::cout << "После изменения размера: Строки = " 
             << table.getRows() 
             << ", Столбцы = " 
             << table.getCols() 
             << std::endl;

   // Проверка ячеек
   table.checkCells(); 
   
   // Заполнение ячеек значениями
   table.setCell(0, 0, Cell("Hello"));
   table.setCell(1, 1, Cell(42.0));
   table.setCell(2, 2, Cell("World"));

   // Проверка ячеек
   table.checkCells(); 

   std::cout << "Все тесты пройдены успешно!" << std::endl;
   return 0;
}
