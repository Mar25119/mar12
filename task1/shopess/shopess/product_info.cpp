#include "product_info.h"

// ����������� � ����������
ProductInfo::ProductInfo(const Product& product, double price, int quantity)
    : product(product) {
    setPrice(price); // ���������� ����� ��������� ����
    setQuantity(quantity); // ���������� ����� ��������� ����������
}

// ����� ��� ��������� ����
double ProductInfo::getPrice() const {
    return price;
}

// ����� ��� ��������� ����������
int ProductInfo::getQuantity() const {
    return quantity;
}

// ����� ���������� ���������� ������
void ProductInfo::decreaseQuantity(int amount) {
    if (amount > quantity) {
        throw std::invalid_argument("Amount exceeds available quantity.");
    }
    quantity -= amount;
}

// ����� ��������� ������
Product ProductInfo::getProduct() const {
    return product;
}

// ����� ��������� ���� � ���������
void ProductInfo::setPrice(double newPrice) {
    if (newPrice < 0) {
        throw std::invalid_argument("Price cannot be negative.");
    }
    price = newPrice;
}

// ����� ��������� ���������� � ���������
void ProductInfo::setQuantity(int newQuantity) {
    if (newQuantity < 0) {
        throw std::invalid_argument("Quantity cannot be negative.");
    }
    quantity = newQuantity;
}