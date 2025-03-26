#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "account.h"
#include "enums.h"

class Account;

class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string passport;
    std::string address;
    std::vector<Account*> accounts;
    ClientStatus status;

public:
    Client(const std::string& firstName, const std::string& lastName,
        const std::string& passport = "", const std::string& address = "");

    void addAccount(Account* account);
    void verify();

    std::string getFullName() const;
    std::string getPassport() const;
    std::string getAddress() const;
    ClientStatus getStatus() const;
    const std::vector<Account*>& getAccounts() const;

    bool isVerified() const;
};

#endif // CLIENT_H