#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Product {

	string title;

	int id;

};

class Shop {

	string title;

	int id;

	vector <ProductInfo> products;

};

class Buyer {

	string name;

	int id;

	int balance;

	map<Product, int>productList;

};

class ProductInfo {

	Product product;

	double price;

	int quantity;

};

class ShopManager {

	vector <Shop> shops;

};