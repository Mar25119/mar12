#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    std::string title; // �������� ������
    int id; // ���������� ������������� ������

public:
    Product(const std::string& title, int id);

    std::string getTitle() const;
    int getId() const;

    // ��� ��������� ������� �� ID
    bool operator<(const Product& other) const;
};

#endif // PRODUCT_H