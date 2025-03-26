#include "debit_account.h"
#include "exceptions.h"

DebitAccount::DebitAccount(const std::string& id, Client* owner, Bank* bank, double interestRate)
    : Account(id, owner, bank), interestRate(interestRate) {
}

void DebitAccount::deposit(double amount) {
    if (amount <= 0) throw InvalidAmountException();
    if (status != AccountStatus::ACTIVE) throw AccountBlockedException();
    balance += amount;
}

void DebitAccount::withdraw(double amount) {
    if (amount <= 0) throw InvalidAmountException();
    if (status != AccountStatus::ACTIVE) throw AccountBlockedException();
    if (balance < amount) throw InsufficientFundsException();
    balance -= amount;
}

void DebitAccount::transfer(Account* to, double amount) {
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

void DebitAccount::applyDailyInterest() {
    if (balance > 0) {
        balance += balance * (interestRate / 36500);
    }
}

std::string DebitAccount::getType() const {
    return "Debit";
}

double DebitAccount::getInterestRate() const {
    return interestRate;
}