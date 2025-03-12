#ifndef PRODUCT_INFO_H
#define PRODUCT_INFO_H

#include "product.h"
#include <stdexcept> // Для std::invalid_argument

class ProductInfo {
private:
    Product product; // Товар
    double price; // Цена товара
    int quantity; // Доступное количество товара

public:
    ProductInfo(const Product& product, double price, int quantity);

    double getPrice() const;
    int getQuantity() const;
    void decreaseQuantity(int amount);
    Product getProduct() const;

    // Метод для установки цены
    void setPrice(double newPrice);

    // Метод для установки количества
    void setQuantity(int newQuantity);
};

#endif // PRODUCT_INFO_H