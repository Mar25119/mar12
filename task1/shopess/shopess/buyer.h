#ifndef BUYER_H
#define BUYER_H

#include <iostream>
#include <vector>
#include <map>
#include "product.h"
#include "shop.h"

class Buyer {
private:
    std::string name; // Имя покупателя
    int id; // Уникальный идентификатор покупателя
    double balance; // Баланс покупателя
    std::map<Product, int> productList; // Список купленных товаров и их количество

public:
    Buyer(const std::string& name, int id, double balance);
    bool purchase(Product product, int quantity, Shop& shop);
    double getBalance() const;
};

#endif // BUYER_H