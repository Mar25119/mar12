#include "bank.h"
#include "client.h"
#include "debit_account.h"
#include "deposit_account.h"
#include "credit_account.h"
#include <stdexcept>
#include <ctime>

Bank::Bank(const std::string& name, CentralBank* centralBank)
    : name(name), centralBank(centralBank),
    debitInterestRate(0.0), creditCommission(0.0), creditLimit(0.0) {
}

Bank::~Bank() {
    for (auto account : accounts) {
        delete account;
    }
    for (auto client : clients) {
        delete client;
    }
}

Client* Bank::addClient(const std::string& firstName, const std::string& lastName,
    const std::string& passport, const std::string& address) {
    Client* client = new Client(firstName, lastName, passport, address);
    clients.push_back(client);
    return client;
}

Account* Bank::createAccount(Client* client, AccountType type, double initialBalance) {
    if (!client) throw std::invalid_argument("Client cannot be null");

    std::string accountId = "ACC" + std::to_string(accounts.size() + 1);
    Account* account = nullptr;

    switch (type) {
    case AccountType::DEBIT:
        account = new DebitAccount(accountId, client, this, debitInterestRate);
        break;
    case AccountType::DEPOSIT:
        account = new DepositAccount(accountId, client, this,
            getDepositRate(initialBalance), 30); // 30 days
        break;
    case AccountType::CREDIT:
        account = new CreditAccount(accountId, client, this,
            creditCommission, creditLimit);
        break;
    }

    if (initialBalance > 0) {
        account->deposit(initialBalance);
    }

    accounts.push_back(account);
    client->addAccount(account);
    return account;
}

void Bank::applyDailyInterest() {
    for (auto account : accounts) {
        account->applyDailyInterest();
    }
}

void Bank::applyMonthlyCommissions() {
    for (auto account : accounts) {
        if (account->getType() == "Credit") {
            dynamic_cast<CreditAccount*>(account)->applyMonthlyCommission();
        }
    }
}

void Bank::setDebitInterestRate(double rate) {
    if (rate < 0) throw std::invalid_argument("Interest rate cannot be negative");
    debitInterestRate = rate;
}

void Bank::setDepositInterestRates(const std::map<double, double>& rates) {
    depositInterestRates = rates;
}
void Bank::setCreditConditions(double commission, double limit) {
    if (commission < 0 || limit < 0)
        throw std::invalid_argument("Commission and limit cannot be negative");
    creditCommission = commission;
    creditLimit = limit;
}

double Bank::getDepositRate(double amount) const {
    if (depositInterestRates.empty()) {
        return 0.0;
    }

    for (auto it = depositInterestRates.rbegin(); it != depositInterestRates.rend(); ++it) {
        if (amount >= it->first) {
            return it->second;
        }
    }

    return 0.0;
}

std::string Bank::getName() const {
    return name;
}

CentralBank* Bank::getCentralBank() const {
    return centralBank;
}

const std::vector<Account*>& Bank::getAccounts() const {
    return accounts;
}

const std::vector<Client*>& Bank::getClients() const {
    return clients;
}