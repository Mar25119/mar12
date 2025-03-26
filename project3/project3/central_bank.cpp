#include "central_bank.h"
#include "bank.h"
#include "transaction.h"
#include <algorithm>
#include <stdexcept>

CentralBank::CentralBank(const std::string& name) : name(name) {}

CentralBank::~CentralBank() {
    for (auto bank : banks) {
        delete bank;
    }
}

void CentralBank::registerBank(Bank* bank) {
    banks.push_back(bank);
}

void CentralBank::processInterbankTransfer(Transaction* transaction) {
    if (!transaction) throw std::invalid_argument("Null transaction");

    try {
        transaction->execute();
        transactions[transaction->getId()] = transaction;
    }
    catch (const std::exception& e) {
        transaction->cancel();
        throw;
    }
}

void CentralBank::cancelTransaction(const std::string& transactionId) {
    auto it = transactions.find(transactionId);
    if (it != transactions.end()) {
        it->second->cancel();
        transactions.erase(it);
    }
    else {
        throw std::runtime_error("Transaction not found");
    }
}

void CentralBank::notifyBanksDaily() {
    for (auto bank : banks) {
        bank->applyDailyInterest();
    }
}

void CentralBank::notifyBanksMonthly() {
    for (auto bank : banks) {
        bank->applyMonthlyCommissions();
    }
}

std::string CentralBank::getName() const {
    return name;
}

const std::vector<Bank*>& CentralBank::getBanks() const {
    return banks;
}