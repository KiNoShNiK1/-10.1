#include <iostream>
#include <cassert>
#include "Table.h"

int main() {
   Table table(2, 2);
   assert(table.getRows() == 2);
   assert(table.getCols() == 2);

   table.resize(3, 3); // изменение размера таблицы

   // Отладочный вывод
   std::cout << "После изменения размера: Строки = " 
             << table.getRows() 
             << ", Столбцы = " 
             << table.getCols() 
             << std::endl;

   // Проверка утверждения
   assert(table.getCols() == 3); // количество столбцов равно 3

   table.checkCells(); // Проверка ячеек

   std::cout << "Все тесты пройдены успешно!" << std::endl;
   return 0;
}
