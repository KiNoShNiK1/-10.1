#include "Table.h"
#include <cassert>
#include <iostream>

Table::Table(size_t rows, size_t cols) : cells(rows, std::vector<Cell*>(cols, nullptr)) {}

Table::~Table() {
    for (auto& row : cells) {
        for (auto& cell : row) {
            delete cell; 
        }
    }
}

size_t Table::getRows() const { 
    return cells.size(); 
}

size_t Table::getCols() const { 
    return cells.empty() ? 0 : cells[0].size(); 
}

Cell* Table::getCell(size_t row, size_t col) const {
    assert(row < cells.size() && col < cells[0].size());
    return cells[row][col];
}

void Table::setCell(size_t row, size_t col, Cell* cell) {
    assert(row < cells.size() && col < cells[0].size());
    delete cells[row][col]; 
    cells[row][col] = cell;
}

void Table::checkCells() const {
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
