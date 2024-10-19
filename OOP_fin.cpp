#include "Table_fin.h"
#include <iostream>
#include <cassert>

int main() {
    Table table(3, 3);
    assert(table.getRows() == 3);
    assert(table.getCols() == 3);

    table.setCell(0, 0, new TextCell("Hello"));
    table.setCell(1, 1, new NumericCell(42.0));
    table.setCell(2, 2, new TextCell("World"));

    table.setCell(0, 1, new FormulaCell(1, 1, 1, 1, "sum"));
    table.setCell(1, 2, new NumericCell(58.0));
    table.setCell(2, 1, new FormulaCell(1, 1, 2, 2, "average"));
    table.setCell(0, 2, new FormulaCell(1, 1, 2, 2, "max"));

    table.checkCells();

    try {
        auto formulaSum = dynamic_cast<FormulaCell*>(table.getCell(0, 1));
        if (formulaSum) {
            double resultSum = formulaSum->calculate(table.getCells());
            std::cout << "Результат суммы: " << resultSum << std::endl;
        }

        auto formulaAvg = dynamic_cast<FormulaCell*>(table.getCell(2, 1));
        if (formulaAvg) {
            double resultAvg = formulaAvg->calculate(table.getCells());
            std::cout << "Результат среднего: " << resultAvg << std::endl;
        }

        auto formulaMax = dynamic_cast<FormulaCell*>(table.getCell(0, 2));
        if (formulaMax) {
            double resultMax = formulaMax->calculate(table.getCells());
            std::cout << "Максимальное значение: " << resultMax << std::endl;
        }

    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    table.clearCell(1, 1);
    table.checkCells();

    table.clearTable();
    table.checkCells();

    return 0;
}
