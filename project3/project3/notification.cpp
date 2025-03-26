#include "notification.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

Notification::Notification(const std::string& message, NotificationType type)
    : message(message), type(type)
{
    time(&timestamp);
}

std::string Notification::getMessage() const
{
    return message;
}

time_t Notification::getTimestamp() const
{
    return timestamp;
}

NotificationType Notification::getType() const
{
    return type;
}

std::string Notification::toString() const
{
    std::tm tm = {};
    if (localtime_s(&tm, &timestamp) != 0) {
        throw std::runtime_error("Failed to convert time");
    }

    std::stringstream ss;
    ss << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] ";

    switch (type) {
    case NotificationType::INFO: ss << "INFO: "; break;
    case NotificationType::WARNING: ss << "WARNING: "; break;
    case NotificationType::ERROR: ss << "ERROR: "; break;
    case NotificationType::TRANSACTION: ss << "TRANSACTION: "; break;
    }

    ss << message;
    return ss.str();
}