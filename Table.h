#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "Cell.h"

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
    
    void checkCells() const;
    const std::vector<std::vector<Cell*>>& getCells() const {
        return cells;
    }
};
};

#endif // TABLE_H
