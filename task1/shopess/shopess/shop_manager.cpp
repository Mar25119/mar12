#include "shop_manager.h"

void ShopManager::addShop(const Shop& shop) {
    shops.push_back(shop);
}

Shop ShopManager::findCheapestShop(const Product& product) {
    double minPrice = std::numeric_limits<double>::max();
    Shop cheapestShop("", 0);

    for (const auto& shop : shops) {
        double price = shop.getPriceOfProduct(product);
        if (price >= 0 && price < minPrice) {
            minPrice = price;
            cheapestShop = shop;
        }
    }
    return cheapestShop;
}

void ShopManager::listAllShops() const {
    for (const auto& shop : shops) {
        std::cout << "Shop ID: " << shop.getId() << ", Title: " << shop.getTitle() << std::endl;
    }
}