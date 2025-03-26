#ifndef BANK_CONSOLE_INTERFACE_H
#define BANK_CONSOLE_INTERFACE_H

#include "central_bank.h"
#include "bank.h"
#include "client.h"
#include "account.h"
#include <iostream>


class BankConsoleInterface {
private:
    CentralBank* centralBank; 
    Bank* currentBank;      
    Client* currentClient;  
    Account* currentAccount; 

    // Navigation methods
    void showMainMenu();    ///< Displays main menu
    void showBankMenu();    ///< Displays bank operations menu
    void showClientMenu();   ///< Displays client operations menu
    void showAccountMenu();  ///< Displays account operations menu

    // Bank operations
    void createBank();      ///< Creates new bank
    void selectBank();      ///< Selects existing bank
    void setBankParameters(); ///< Configures bank parameters

    // Client operations
    void createClient();    ///< Creates new client
    void selectClient();    ///< Selects existing client

    // Account operations
    void createAccount();   ///< Creates new account
    void selectAccount();   ///< Selects existing account
    void performDeposit();  ///< Performs deposit operation
    void performWithdraw(); ///< Performs withdrawal operation
    void performTransfer(); ///< Performs transfer operation
    void showAccountInfo(); ///< Displays account information

public:
   
    explicit BankConsoleInterface(CentralBank* cb);

   
    void run();
};

#endif // BANK_CONSOLE_INTERFACE_H