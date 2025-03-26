#include "central_bank.h"
#include "bank_console_interface.h"
#include <memory>

int main() {
    try {
        // Создаем центральный банк
        CentralBank centralBank("Central Bank of Russia");

        // Создаем интерфейс
        BankConsoleInterface interface(&centralBank);

        // Запускаем интерфейс
        interface.run();

    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}