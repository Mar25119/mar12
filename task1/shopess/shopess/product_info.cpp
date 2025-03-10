#include "product_info.h"

// Конструктор с проверками
ProductInfo::ProductInfo(const Product& product, double price, int quantity)
    : product(product) {
    setPrice(price); // Используем метод установки цены
    setQuantity(quantity); // Используем метод установки количества
}

// Метод для получения цены
double ProductInfo::getPrice() const {
    return price;
}

// Метод для получения количества
int ProductInfo::getQuantity() const {
    return quantity;
}

// Метод уменьшения количества товара
void ProductInfo::decreaseQuantity(int amount) {
    if (amount > quantity) {
        throw std::invalid_argument("Amount exceeds available quantity.");
    }
    quantity -= amount;
}

// Метод получения товара
Product ProductInfo::getProduct() const {
    return product;
}

// Метод установки цены с проверкой
void ProductInfo::setPrice(double newPrice) {
    if (newPrice < 0) {
        throw std::invalid_argument("Price cannot be negative.");
    }
    price = newPrice;
}

// Метод установки количества с проверкой
void ProductInfo::setQuantity(int newQuantity) {
    if (newQuantity < 0) {
        throw std::invalid_argument("Quantity cannot be negative.");
    }
    quantity = newQuantity;
}