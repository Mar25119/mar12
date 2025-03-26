#include "transaction.h"
#include "account.h"
#include "exceptions.h"
#include <ctime>
#include <stdexcept>

Transaction::Transaction(const std::string& id, Account* from, Account* to,
    double amount, const std::string& description)
    : id(id), from(from), to(to), amount(amount), description(description),
    status(TransactionStatus::PENDING)
{
    if (time(&timestamp) == -1) {
        throw std::runtime_error("Failed to get current time");
    }
}

void Transaction::execute() {
    if (status != TransactionStatus::PENDING) {
        throw InvalidTransactionException();
    }

    if (from) {
        from->transfer(to, amount);
    }
    else {
        to->deposit(amount);
    }

    status = TransactionStatus::COMPLETED;
}

void Transaction::cancel() {
    if (status != TransactionStatus::COMPLETED) {
        throw InvalidTransactionException();
    }

    if (from) {
        try {
            to->transfer(from, amount);
        }
        catch (...) {
            // If cancel fails, mark as failed
            status = TransactionStatus::FAILED;
            throw;
        }
    }
    else {
        try {
            to->withdraw(amount);
        }
        catch (...) {
            status = TransactionStatus::FAILED;
            throw;
        }
    }

    status = TransactionStatus::CANCELLED;
}

std::string Transaction::getId() const {
    return id;
}

Account* Transaction::getFromAccount() const {
    return from;
}
Account* Transaction::getToAccount() const {
    return to;
}

double Transaction::getAmount() const {
    return amount;
}

time_t Transaction::getTimestamp() const {
    return timestamp;
}

TransactionStatus Transaction::getStatus() const {
    return status;
}

std::string Transaction::getDescription() const {
    return description;
}