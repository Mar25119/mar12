#include "bank_console_interface.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <ctime>

BankConsoleInterface::BankConsoleInterface(CentralBank* cb) : centralBank(cb),
currentBank(nullptr), currentClient(nullptr), currentAccount(nullptr) {
}

void BankConsoleInterface::run() {
    while (true) {
        try {
            if (!currentBank) {
                showMainMenu();
            }
            else if (!currentClient) {
                showBankMenu();
            }
            else if (!currentAccount) {
                showClientMenu();
            }
            else {
                showAccountMenu();
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void BankConsoleInterface::showMainMenu() {
    std::cout << "\n=== Central Bank: " << centralBank->getName() << " ===" << std::endl;
    std::cout << "1. Create new bank\n";
    std::cout << "2. Select bank\n";
    std::cout << "3. Exit\n";
    std::cout << "Choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1: createBank(); break;
    case 2: selectBank(); break;
    case 3: exit(0);
    default: throw std::invalid_argument("Invalid choice");
    }
}

void BankConsoleInterface::showBankMenu() {
    std::cout << "\n=== Bank: " << currentBank->getName() << " ===" << std::endl;
    std::cout << "1. Create new client\n";
    std::cout << "2. Select client\n";
    std::cout << "3. Set bank parameters\n";
    std::cout << "4. Back to main menu\n";
    std::cout << "Choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1: createClient(); break;
    case 2: selectClient(); break;
    case 3: setBankParameters(); break;
    case 4:
        currentBank = nullptr;
        currentClient = nullptr;
        currentAccount = nullptr;
        break;
    default: throw std::invalid_argument("Invalid choice");
    }
}

void BankConsoleInterface::showClientMenu() {
    std::cout << "\n=== Client: " << currentClient->getFullName() << " ===" << std::endl;
    std::cout << "1. Create account\n";
    std::cout << "2. Select account\n";
    std::cout << "3. Verify client\n";
    std::cout << "4. Back to bank menu\n";
    std::cout << "Choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1: createAccount(); break;
    case 2: selectAccount(); break;
    case 3:
        currentClient->verify();
        std::cout << "Client verified successfully!\n";
        break;
    case 4:
        currentClient = nullptr;
        currentAccount = nullptr;
        break;
    default: throw std::invalid_argument("Invalid choice");
    }
}

void BankConsoleInterface::showAccountMenu() {
    std::cout << "\n=== Account: " << currentAccount->getId() << " ("
        << currentAccount->getType() << ") ===" << std::endl;
    std::cout << "Balance: " << currentAccount->getBalance() << std::endl;
    std::cout << "1. Deposit\n";
    std::cout << "2. Withdraw\n";
    std::cout << "3. Transfer\n";
    std::cout << "4. Show info\n";
    std::cout << "5. Back to client menu\n";
    std::cout << "Choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1: performDeposit(); break;
    case 2: performWithdraw(); break;
    case 3: performTransfer(); break;
    case 4: showAccountInfo(); break;
    case 5:
        currentAccount = nullptr;
        break;
    default: throw std::invalid_argument("Invalid choice");
    }
}

void BankConsoleInterface::createBank() {
    std::string name;
    std::cout << "Enter bank name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    Bank* bank = new Bank(name, centralBank);
    centralBank->registerBank(bank);
    currentBank = bank;
    std::cout << "Bank created successfully!\n";
}
void BankConsoleInterface::selectBank() {
    const auto& banks = centralBank->getBanks();
    if (banks.empty()) {
        throw std::runtime_error("No banks available");
    }

    std::cout << "\nAvailable banks:\n";
    for (size_t i = 0; i < banks.size(); ++i) {
        std::cout << (i + 1) << ". " << banks[i]->getName() << "\n";
    }

    std::cout << "Select bank: ";
    size_t choice;
    std::cin >> choice;

    if (choice < 1 || choice > banks.size()) {
        throw std::invalid_argument("Invalid bank selection");
    }

    currentBank = banks[choice - 1];
    std::cout << "Selected bank: " << currentBank->getName() << "\n";
}

void BankConsoleInterface::createClient() {
    std::string firstName, lastName, passport, address;

    std::cout << "Enter first name: ";
    std::cin >> firstName;

    std::cout << "Enter last name: ";
    std::cin >> lastName;

    std::cout << "Enter passport (optional): ";
    std::cin.ignore();
    std::getline(std::cin, passport);

    std::cout << "Enter address (optional): ";
    std::getline(std::cin, address);

    Client* client = currentBank->addClient(firstName, lastName, passport, address);
    currentClient = client;
    std::cout << "Client created successfully!\n";
}

void BankConsoleInterface::selectClient() {
    const auto& clients = currentBank->getClients();
    if (clients.empty()) {
        throw std::runtime_error("No clients available");
    }

    std::cout << "\nAvailable clients:\n";
    for (size_t i = 0; i < clients.size(); ++i) {
        std::cout << (i + 1) << ". " << clients[i]->getFullName();
        if (clients[i]->isVerified()) std::cout << " (verified)";
        std::cout << "\n";
    }

    std::cout << "Select client: ";
    size_t choice;
    std::cin >> choice;

    if (choice < 1 || choice > clients.size()) {
        throw std::invalid_argument("Invalid client selection");
    }

    currentClient = clients[choice - 1];
    std::cout << "Selected client: " << currentClient->getFullName() << "\n";
}

void BankConsoleInterface::setBankParameters() {
    std::cout << "\n=== Set Bank Parameters ===" << std::endl;

    // Дебетовые счета
    double debitRate;
    std::cout << "Enter debit interest rate (%): ";
    std::cin >> debitRate;
    currentBank->setDebitInterestRate(debitRate);

    // Кредитные счета
    double commission, limit;
    std::cout << "Enter credit commission: ";
    std::cin >> commission;
    std::cout << "Enter credit limit: ";
    std::cin >> limit;
    currentBank->setCreditConditions(commission, limit);

    // Депозитные счета
    std::map<double, double> depositRates;
    std::cout << "Enter deposit rates (amount rate, 0 to finish):\n";
    while (true) {
        double amount, rate;
        std::cout << "Amount: ";
        std::cin >> amount;
        if (amount <= 0) break;
        std::cout << "Rate (%): ";
        std::cin >> rate;
        depositRates[amount] = rate;
    }
    currentBank->setDepositInterestRates(depositRates);

    std::cout << "Bank parameters updated successfully!\n";
}

void BankConsoleInterface::createAccount() {
    std::cout << "\n=== Create Account ===" << std::endl;
    std::cout << "1. Debit account\n";
    std::cout << "2. Deposit account\n";
    std::cout << "3. Credit account\n";
    std::cout << "Choice: ";

    int choice;
    std::cin >> choice;

    AccountType type;
    switch (choice) {
    case 1: type = AccountType::DEBIT; break;
    case 2: type = AccountType::DEPOSIT; break;
    case 3: type = AccountType::CREDIT; break;
    default: throw std::invalid_argument("Invalid choice");
    }

    double initialBalance = 0;
    if (type == AccountType::DEPOSIT) {
        std::cout << "Enter initial deposit amount: ";
        std::cin >> initialBalance;
    }

    Account* account = currentBank->createAccount(currentClient, type, initialBalance);
    currentAccount = account;
    std::cout << "Account created successfully! ID: " << account->getId() << "\n";
}
void BankConsoleInterface::selectAccount() {
    const auto& accounts = currentClient->getAccounts();
    if (accounts.empty()) {
        throw std::runtime_error("No accounts available");
    }

    std::cout << "\nAvailable accounts:\n";
    for (size_t i = 0; i < accounts.size(); ++i) {
        std::cout << (i + 1) << ". " << accounts[i]->getId() << " ("
            << accounts[i]->getType() << ") - "
            << accounts[i]->getBalance() << "\n";
    }

    std::cout << "Select account: ";
    size_t choice;
    std::cin >> choice;

    if (choice < 1 || choice > accounts.size()) {
        throw std::invalid_argument("Invalid account selection");
    }

    currentAccount = accounts[choice - 1];
    std::cout << "Selected account: " << currentAccount->getId() << "\n";
}

void BankConsoleInterface::performDeposit() {
    double amount;
    std::cout << "Enter amount to deposit: ";
    std::cin >> amount;

    currentAccount->deposit(amount);
    std::cout << "Deposit successful. New balance: " << currentAccount->getBalance() << "\n";
}

void BankConsoleInterface::performWithdraw() {
    double amount;
    std::cout << "Enter amount to withdraw: ";
    std::cin >> amount;

    currentAccount->withdraw(amount);
    std::cout << "Withdrawal successful. New balance: " << currentAccount->getBalance() << "\n";
}

void BankConsoleInterface::performTransfer() {
    std::cout << "\n=== Transfer ===" << std::endl;

    // Выбор банка получателя
    const auto& banks = centralBank->getBanks();
    std::cout << "Select recipient bank:\n";
    for (size_t i = 0; i < banks.size(); ++i) {
        std::cout << (i + 1) << ". " << banks[i]->getName() << "\n";
    }
    std::cout << "Choice: ";
    size_t bankChoice;
    std::cin >> bankChoice;
    if (bankChoice < 1 || bankChoice > banks.size()) {
        throw std::invalid_argument("Invalid bank selection");
    }
    Bank* recipientBank = banks[bankChoice - 1];

    // Выбор счета получателя
    const auto& accounts = recipientBank->getAccounts();
    std::cout << "Select recipient account:\n";
    for (size_t i = 0; i < accounts.size(); ++i) {
        std::cout << (i + 1) << ". " << accounts[i]->getId() << " ("
            << accounts[i]->getType() << ") - "
            << accounts[i]->getOwner()->getFullName() << "\n";
    }
    std::cout << "Choice: ";
    size_t accountChoice;
    std::cin >> accountChoice;
    if (accountChoice < 1 || accountChoice > accounts.size()) {
        throw std::invalid_argument("Invalid account selection");
    }
    Account* recipientAccount = accounts[accountChoice - 1];

    double amount;
    std::cout << "Enter amount to transfer: ";
    std::cin >> amount;

    currentAccount->transfer(recipientAccount, amount);
    std::cout << "Transfer successful. New balance: " << currentAccount->getBalance() << "\n";
}

void BankConsoleInterface::showAccountInfo() {
    std::cout << "\n=== Account Info ===" << std::endl;
    std::cout << "ID: " << currentAccount->getId() << "\n";
    std::cout << "Type: " << currentAccount->getType() << "\n";
    std::cout << "Balance: " << currentAccount->getBalance() << "\n";
    std::cout << "Owner: " << currentAccount->getOwner()->getFullName() << "\n";
    std::cout << "Bank: " << currentAccount->getBank()->getName() << "\n";
    std::cout << "Status: " << (currentAccount->getStatus() == AccountStatus::ACTIVE ? "Active" : "Blocked") << "\n";
}