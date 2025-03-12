#include "product.h"

Product::Product(const std::string& title, int id) : title(title), id(id) {}

std::string Product::getTitle() const {
    return title;
}

int Product::getId() const {
    return id;
}

bool Product::operator<(const Product& other) const {
    return id < other.id;
}