#include "buyer.h"

Buyer::Buyer(const std::string& name, int id, double balance)
    : name(name), id(id), balance(balance) {
}

bool Buyer::purchase(Product product, int quantity, Shop& shop) {
    double price = shop.getPriceOfProduct(product);
    if (price >= 0 && shop.sellProduct(product, quantity) && (balance >= price * quantity)) {
        balance -= price * quantity;
        productList[product] += quantity; // ”величиваем количество купленных товаров
        std::cout << "Purchased " << quantity << " of " << product.getTitle() << std::endl;
        return true;
    }
    std::cout << "Purchase failed for " << product.getTitle() << std::endl;
    return false;
}

double Buyer::getBalance() const {
    return balance;
}