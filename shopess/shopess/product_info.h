#ifndef PRODUCT_INFO_H
#define PRODUCT_INFO_H

#include "product.h"

class ProductInfo {
private:
    Product product; // товар
    double price; // цена товара
    int quantity; // доступное количество товара

public:
    ProductInfo(const Product& product, double price, int quantity)
        : product(product), price(price), quantity(quantity) {
    }

    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void decreaseQuantity(int amount) { quantity -= amount; }

    Product getProduct() const { return product; }
};

#endif // PRODUCT_INFO_H