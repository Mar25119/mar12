#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include "account.h"
#include "enums.h"

class Account;

class Transaction {
private:
    std::string id;
    Account* from;
    Account* to;
    double amount;
    time_t timestamp;
    TransactionStatus status;
    std::string description;

public:
    Transaction(const std::string& id, Account* from, Account* to,
        double amount, const std::string& description = "");

    void execute();
    void cancel();

    std::string getId() const;
    Account* getFromAccount() const;
    Account* getToAccount() const;
    double getAmount() const;
    time_t getTimestamp() const;
    TransactionStatus getStatus() const;
    std::string getDescription() const;
};

#endif // TRANSACTION_H