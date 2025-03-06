#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include <string>
#include "product_info.h"

class Shop {
private:
    std::string title; // Название магазина
    int id; // Уникальный идентификатор магазина
    std::vector<ProductInfo> products; // Список товаров

public:
    Shop(const std::string& title, int id) : title(title), id(id) {}

    void addProduct(const ProductInfo& productInfo) {
        products.push_back(productInfo);
    }

    bool sellProduct(const Product& product, int quantity) {
        for (auto& productInfo : products) {
            if (productInfo.getProduct().getId() == product.getId() && productInfo.getQuantity() >= quantity) {
                productInfo.decreaseQuantity(quantity);
                return true;
            }
        }
        return false;
    }

    std::string getTitle() const { return title; }
    double getPriceOfProduct(const Product& product) const {
        for (const auto& productInfo : products) {
            if (productInfo.getProduct().getId() == product.getId()) {
                return productInfo.getPrice();
            }
        }
        return -1; // Если товар не найден
    }

    int getId() const { return id; }
    const std::vector<ProductInfo>& getProducts() const { return products; }
};

#endif // SHOP_H