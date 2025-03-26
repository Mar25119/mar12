#ifndef DEPOSIT_ACCOUNT_H
#define DEPOSIT_ACCOUNT_H

#include "account.h"
#include <ctime>

class DepositAccount : public Account {
private:
    double interestRate;
    time_t creationDate;
    time_t endDate;

public:
    DepositAccount(const std::string& id, Client* owner, Bank* bank,
        double interestRate, time_t durationDays);

    void deposit(double amount) override;
    void withdraw(double amount) override;
    void transfer(Account* to, double amount) override;
    void applyDailyInterest() override;

    std::string getType() const override;
    time_t getEndDate() const;
    bool isTermExpired() const;
};

#endif // DEPOSIT_ACCOUNT_H