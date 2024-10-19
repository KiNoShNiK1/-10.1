#include "Table_fin.h"

Table::Table(size_t rows, size_t cols)
    : cells(rows, std::vector<Cell*>(cols, nullptr)) {}

Table::~Table() {
    clearTable();
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

void Table::clearCell(size_t row, size_t col) {
    assert(row < cells.size() && col < cells[0].size());
    delete cells[row][col];
    cells[row][col] = nullptr;
}

void Table::clearTable() {
    for (auto& row : cells) {
        for (auto& cell : row) {
            delete cell;
            cell = nullptr;
        }
    }
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

void Table::resize(size_t newRows, size_t newCols) {
    cells.resize(newRows);
    for (auto& row : cells) {
        row.resize(newCols, nullptr);
    }
}

const std::vector<std::vector<Cell*>>& Table::getCells() const {
    return cells;
}
