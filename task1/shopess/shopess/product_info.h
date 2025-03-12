#ifndef PRODUCT_INFO_H
#define PRODUCT_INFO_H

#include "product.h"
#include <stdexcept> // ��� std::invalid_argument

class ProductInfo {
private:
    Product product; // �����
    double price; // ���� ������
    int quantity; // ��������� ���������� ������

public:
    ProductInfo(const Product& product, double price, int quantity);

    double getPrice() const;
    int getQuantity() const;
    void decreaseQuantity(int amount);
    Product getProduct() const;

    // ����� ��� ��������� ����
    void setPrice(double newPrice);

    // ����� ��� ��������� ����������
    void setQuantity(int newQuantity);
};

#endif // PRODUCT_INFO_H