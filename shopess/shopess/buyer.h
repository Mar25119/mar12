#ifndef BUYER_H
#define BUYER_H

#include <iostream>
#include <vector>
#include <map>
#include "product.h"

class Buyer {
private:
    std::string name; // ��� ����������
    int id; // ���������� ������������� ����������
    double balance; // ������ ����������
    std::map<Product, int> productList; // ������ ��������� ������� � �� ����������

public:
    Buyer(const std::string& name, int id, double balance)
        : name(name), id(id), balance(balance) {
    }

    bool purchase(Product product, int quantity, Shop& shop) {
        double price = shop.getPriceOfProduct(product);
        if (price >= 0 && shop.sellProduct(product, quantity) && (balance >= price * quantity)) {
            balance -= price * quantity;
            productList[product] += quantity; // ����������� ���������� ��������� �������
            std::cout << "Purchased " << quantity << " of " << product.getTitle() << std::endl;
            return true;
        }
        std::cout << "Purchase failed for " << product.getTitle() << std::endl;
        return false;
    }

    double getBalance() const { return balance; }
};

#endif // BUYER_H