#include "Table.h"
#include <iostream>
#include <cassert>

Table::Table() {}

Table::Table(size_t rows, size_t cols) : cells(rows, std::vector<Cell>(cols)) {}

size_t Table::getRows() const { return cells.size(); }

size_t Table::getCols() const {
    return cells.empty() ? 0 : cells[0].size();
}

Cell Table::getCell(size_t row, size_t col) const {
    assert(row < cells.size() && col < cells[0].size());
    return cells[row][col];
}

void Table::setCell(size_t row, size_t col, const Cell& cell) {
    assert(row < cells.size() && col < cells[0].size());
    cells[row][col] = cell;
}

void Table::resize(size_t rows, size_t cols) {
    cells.resize(rows);
    for (auto& row : cells) {
        row.resize(cols);
    }
}

void Table::checkCells() const {
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
