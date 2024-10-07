#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "Cell.h"

class Table {
private:
    std::vector<std::vector<Cell>> cells;

public:
    // Конструкторы
    Table();
    Table(size_t rows, size_t cols);

    // Методы доступа
    size_t getRows() const;
    size_t getCols() const;
    Cell getCell(size_t row, size_t col) const;

    // Методы изменения состояния
    void setCell(size_t row, size_t col, const Cell& cell);
    void resize(size_t rows, size_t cols);
    
    // Метод проверки ячеек
    void checkCells() const;
};

#endif // TABLE_H
