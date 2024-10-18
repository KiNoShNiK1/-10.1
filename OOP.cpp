#include <iostream>
#include <cassert>
#include "Table.h"
#include "Cell.h"

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
