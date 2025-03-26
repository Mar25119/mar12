#include "client.h"
#include "account.h"
#include <stdexcept>

Client::Client(const std::string& firstName, const std::string& lastName,
    const std::string& passport, const std::string& address)
    : firstName(firstName), lastName(lastName),
    passport(passport), address(address),
    status(ClientStatus::UNVERIFIED) {
}

void Client::addAccount(Account* account) {
    if (!account) throw std::invalid_argument("Account cannot be null");
    accounts.push_back(account);
}

void Client::verify() {
    status = ClientStatus::VERIFIED;
}

std::string Client::getFullName() const {
    return firstName + " " + lastName;
}

std::string Client::getPassport() const {
    return passport;
}

std::string Client::getAddress() const {
    return address;
}

ClientStatus Client::getStatus() const {
    return status;
}

const std::vector<Account*>& Client::getAccounts() const {
    return accounts;
}

bool Client::isVerified() const {
    return status == ClientStatus::VERIFIED;
}