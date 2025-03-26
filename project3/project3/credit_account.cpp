#include "credit_account.h"
#include "exceptions.h"

CreditAccount::CreditAccount(const std::string& id, Client* owner, Bank* bank,
    double commission, double creditLimit)
    : Account(id, owner, bank), commission(commission), creditLimit(creditLimit) {
}

void CreditAccount::deposit(double amount) {
    if (amount <= 0) throw InvalidAmountException();
    if (status != AccountStatus::ACTIVE) throw AccountBlockedException();
    balance += amount;
}

void CreditAccount::withdraw(double amount) {
    if (amount <= 0) throw InvalidAmountException();
    if (status != AccountStatus::ACTIVE) throw AccountBlockedException();
    if (balance - amount < -creditLimit) throw InsufficientFundsException();
    balance -= amount;
}

void CreditAccount::transfer(Account* to, double amount) {
    if (!to) throw std::invalid_argument("Target account cannot be null");
    withdraw(amount);
    try {
        to->deposit(amount);
    }
    catch (...) {
        deposit(amount); // Rollback
        throw;
    }
}

void CreditAccount::applyDailyInterest() {
    // No daily interest for credit accounts
}

void CreditAccount::applyMonthlyCommission() {
    if (balance < 0) {
        balance -= commission;
    }
}

std::string CreditAccount::getType() const {
    return "Credit";
}

double CreditAccount::getCommission() const {
    return commission;
}

double CreditAccount::getCreditLimit() const {
    return creditLimit;
}