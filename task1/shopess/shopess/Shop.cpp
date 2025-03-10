#include "shop.h"

Shop::Shop(const std::string& title, int id) : title(title), id(id) {}

void Shop::addProduct(const ProductInfo& productInfo) {
    products.push_back(productInfo);
}

bool Shop::sellProduct(const Product& product, int quantity) {
    for (auto& productInfo : products) {
        if (productInfo.getProduct().getId() == product.getId() && productInfo.getQuantity() >= quantity) {
            productInfo.decreaseQuantity(quantity);
            return true;
        }
    }
    return false;
}
std::string Shop::getTitle() const {
    return title;
}

double Shop::getPriceOfProduct(const Product& product) const {
    for (const auto& productInfo : products) {
        if (productInfo.getProduct().getId() == product.getId()) {
            return productInfo.getPrice();
        }
    }
    return -1; // Если товар не найден
}

int Shop::getId() const {
    return id;
}

const std::vector<ProductInfo>& Shop::getProducts() const {
    return products;
}