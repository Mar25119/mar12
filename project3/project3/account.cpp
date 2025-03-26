#include "account.h"
#include "exceptions.h"

Account::Account(const std::string& id, Client* owner, Bank* bank)
    : id(id), owner(owner), bank(bank), balance(0.0), status(AccountStatus::ACTIVE) {
}

double Account::getBalance() const {
    return balance;
}

std::string Account::getId() const {
    return id;
}

AccountStatus Account::getStatus() const {
    return status;
}

Client* Account::getOwner() const {
    return owner;
}

Bank* Account::getBank() const {
    return bank;
}

void Account::block() {
    status = AccountStatus::BLOCKED;
}

void Account::unblock() {
    status = AccountStatus::ACTIVE;
}