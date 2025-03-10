#ifndef SHOP_MANAGER_H
#define SHOP_MANAGER_H

#include <iostream>
#include <vector>
#include "shop.h"

class ShopManager {
private:
    std::vector<Shop> shops;

public:
    void addShop(const Shop& shop);
    Shop findCheapestShop(const Product& product);
    void listAllShops() const;
};

#endif // SHOP_MANAGER_H