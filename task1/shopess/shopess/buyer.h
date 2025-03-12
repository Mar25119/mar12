#ifndef BUYER_H
#define BUYER_H

#include <iostream>
#include <vector>
#include <map>
#include "product.h"
#include "shop.h"

class Buyer {
private:
    std::string name; // ��� ����������
    int id; // ���������� ������������� ����������
    double balance; // ������ ����������
    std::map<Product, int> productList; // ������ ��������� ������� � �� ����������

public:
    Buyer(const std::string& name, int id, double balance);
    bool purchase(Product product, int quantity, Shop& shop);
    double getBalance() const;
};

#endif // BUYER_H