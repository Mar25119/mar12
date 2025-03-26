#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "client.h"
#include "bank.h"
#include "enums.h"

class Bank;
class Client;
class Transaction;

class Account {
protected:
    double balance;
    std::string id;
    Client* owner;
    Bank* bank;
    AccountStatus status;

public:
    Account(const std::string& id, Client* owner, Bank* bank);
    virtual ~Account() = default;

    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void transfer(Account* to, double amount) = 0;
    virtual void applyDailyInterest() = 0;

    virtual std::string getType() const = 0;
    double getBalance() const;
    std::string getId() const;
    AccountStatus getStatus() const;
    Client* getOwner() const;
    Bank* getBank() const;

    void block();
    void unblock();
};

#endif // ACCOUNT_H