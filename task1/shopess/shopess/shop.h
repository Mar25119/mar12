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
    Shop(const std::string& title, int id);

    void addProduct(const ProductInfo& productInfo);
    bool sellProduct(const Product& product, int quantity);

    std::string getTitle() const;
    double getPriceOfProduct(const Product& product) const;
    int getId() const;
    const std::vector<ProductInfo>& getProducts() const;
};

#endif // SHOP_H