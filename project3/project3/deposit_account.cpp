#include "deposit_account.h"
#include "exceptions.h"
#include <ctime>
#include <cmath>
#include <stdexcept>

DepositAccount::DepositAccount(const std::string& id, Client* owner, Bank* bank,
    double interestRate, time_t durationDays)
    : Account(id, owner, bank), interestRate(interestRate)
{
    if (time(&creationDate) == -1) {
        throw std::runtime_error("Failed to get current time");
    }
    endDate = creationDate + durationDays * 24 * 60 * 60;
}
void DepositAccount::deposit(double amount) {
    if (amount <= 0) throw InvalidAmountException();
    if (status != AccountStatus::ACTIVE) throw AccountBlockedException();
    balance += amount;
}

void DepositAccount::withdraw(double amount) {
    if (amount <= 0) throw InvalidAmountException();
    if (status != AccountStatus::ACTIVE) throw AccountBlockedException();
    if (!isTermExpired()) throw AccountTermException();
    if (balance < amount) throw InsufficientFundsException();
    balance -= amount;
}

void DepositAccount::transfer(Account* to, double amount) {
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

void DepositAccount::applyDailyInterest() {
    if (balance > 0) {
        balance += balance * (interestRate / 36500);
    }
}

std::string DepositAccount::getType() const {
    return "Deposit";
}

time_t DepositAccount::getEndDate() const {
    return endDate;
}

bool DepositAccount::isTermExpired() const {
    time_t now;
    time(&now);
    return now >= endDate;
}