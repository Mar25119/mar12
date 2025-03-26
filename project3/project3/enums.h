#ifndef ENUMS_H
#define ENUMS_H

enum class AccountType {
    DEBIT,
    DEPOSIT,
    CREDIT
};

enum class AccountStatus {
    ACTIVE,
    BLOCKED,
    CLOSED
};

enum class TransactionStatus {
    PENDING,
    COMPLETED,
    CANCELLED,
    FAILED
};

enum class ClientStatus {
    UNVERIFIED,
    VERIFIED
};

enum class NotificationType {
    INFO,
    WARNING,
    ERROR,
    TRANSACTION
};

#endif // ENUMS_H