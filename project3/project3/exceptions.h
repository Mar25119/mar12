#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class BankException : public std::exception {
protected:
    std::string message;
public:
    explicit BankException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException() : BankException("Insufficient funds in account") {}
};

class AccountBlockedException : public BankException {
public:
    AccountBlockedException() : BankException("Account is blocked or restricted") {}
};

class InvalidAmountException : public BankException {
public:
    InvalidAmountException() : BankException("Invalid amount specified") {}
};
class InvalidTransactionException : public BankException {
public:
    InvalidTransactionException() : BankException("Invalid transaction attempted") {}
};

class AccountTermException : public BankException {
public:
    AccountTermException() : BankException("Account term restrictions apply") {}
};

#endif // EXCEPTIONS_H