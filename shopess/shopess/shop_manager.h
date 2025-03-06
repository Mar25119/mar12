#ifndef SHOP_MANAGER_H
#define SHOP_MANAGER_H

#include <iostream>
#include <vector>
#include "shop.h"

class ShopManager {
private:
    std::vector<Shop> shops;

public:
    void addShop(const Shop& shop) {
        shops.push_back(shop);
    }

    Shop findCheapestShop(const Product& product) {
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

    void listAllShops() const {
        for (const auto& shop : shops) {
            std::cout << "Shop ID: " << shop.getId() << ", Title: " << shop.getTitle() << std::endl;
        }
    }
};

#endif // SHOP_MANAGER_H