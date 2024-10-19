#ifndef TABLE_FIN_H
#define TABLE_FIN_H

#include "Cell_fin.h"
#include <vector>
#include <cassert>
#include <iostream>

class Table {
private:
    std::vector<std::vector<Cell*>> cells;

public:
    Table(size_t rows, size_t cols);
    ~Table();

    size_t getRows() const;
    size_t getCols() const;

    Cell* getCell(size_t row, size_t col) const;
    void setCell(size_t row, size_t col, Cell* cell);
    void clearCell(size_t row, size_t col);
    void clearTable();
    void checkCells() const;
    void resize(size_t newRows, size_t newCols);
    const std::vector<std::vector<Cell*>>& getCells() const;
};

#endif
