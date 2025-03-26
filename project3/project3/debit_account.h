#ifndef DEBIT_ACCOUNT_H
#define DEBIT_ACCOUNT_H

#include "account.h"
class DebitAccount : public Account {
private:
    double interestRate;

public:
    DebitAccount(const std::string& id, Client* owner, Bank* bank, double interestRate);

    void deposit(double amount) override;
    void withdraw(double amount) override;
    void transfer(Account* to, double amount) override;
    void applyDailyInterest() override;

    std::string getType() const override;
    double getInterestRate() const;
};

#endif // DEBIT_ACCOUNT_H