#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
#include <ctime>
#include "enums.h"

class Notification {
private:
    std::string message;
    time_t timestamp;
    NotificationType type;

public:
    Notification(const std::string& message, NotificationType type);

    std::string getMessage() const;
    time_t getTimestamp() const;
    NotificationType getType() const;
    std::string toString() const;
};

#endif // NOTIFICATION_H