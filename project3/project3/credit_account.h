#ifndef CREDIT_ACCOUNT_H
#define CREDIT_ACCOUNT_H

#include "account.h"

class CreditAccount : public Account {
private:
    double commission;
    double creditLimit;

public:
    CreditAccount(const std::string& id, Client* owner, Bank* bank,
        double commission, double creditLimit);

    void deposit(double amount) override;
    void withdraw(double amount) override;
    void transfer(Account* to, double amount) override;
    void applyDailyInterest() override;
    void applyMonthlyCommission();

    std::string getType() const override;
    double getCommission() const;
    double getCreditLimit() const;
};

#endif // CREDIT_ACCOUNT_H