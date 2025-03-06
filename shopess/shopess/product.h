#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    std::string title; // Название товара
    int id; // Уникальный идентификатор товара

public:
    Product(const std::string& title, int id) : title(title), id(id) {}
    std::string getTitle() const { return title; }
    int getId() const { return id; }
    // Для сравнения товаров по ID
    bool operator<(const Product& other) const {
        return id < other.id;
    }
};

#endif // PRODUCT_H