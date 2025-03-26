#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include <map>
#include "client.h"
#include "account.h"
#include "central_bank.h"
#include "enums.h"

class CentralBank;
class Client;
class Account;

class Bank {
private:
    std::string name;
    CentralBank* centralBank;
    std::vector<Account*> accounts;
    std::vector<Client*> clients;

    // Банковские параметры
    double debitInterestRate;
    std::map<double, double> depositInterestRates; // сумма -> процент
    double creditCommission;
    double creditLimit;

public:
    Bank(const std::string& name, CentralBank* centralBank);
    ~Bank();

    Client* addClient(const std::string& firstName, const std::string& lastName,
        const std::string& passport = "", const std::string& address = "");
    Account* createAccount(Client* client, AccountType type, double initialBalance = 0);

    void applyDailyInterest();
    void applyMonthlyCommissions();

    void setDebitInterestRate(double rate);
    void setDepositInterestRates(const std::map<double, double>& rates);
    void setCreditConditions(double commission, double limit);

    std::string getName() const;
    CentralBank* getCentralBank() const;
    const std::vector<Account*>& getAccounts() const;
    const std::vector<Client*>& getClients() const;

    
    double getDepositRate(double amount) const;
};

#endif // BANK_H