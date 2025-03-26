#ifndef CENTRAL_BANK_H
#define CENTRAL_BANK_H

#include <string>
#include <vector>
#include <unordered_map>
#include "bank.h"
#include "transaction.h"

class Bank;
class Transaction;

class CentralBank {
private:
    std::string name;
    std::vector<Bank*> banks;
    std::unordered_map<std::string, Transaction*> transactions;

public:
    explicit CentralBank(const std::string& name);
    ~CentralBank();

    void registerBank(Bank* bank);
    void processInterbankTransfer(Transaction* transaction);
    void cancelTransaction(const std::string& transactionId);
    void notifyBanksDaily();
    void notifyBanksMonthly();

    std::string getName() const;
    const std::vector<Bank*>& getBanks() const;
};

#endif // CENTRAL_BANK_H