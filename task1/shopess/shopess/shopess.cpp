#include "shop_manager.h"
#include "buyer.h"

int main() {
    ShopManager manager;

    // Создаем продукты
    Product apple("Apple", 1);
    Product banana("Banana", 2);
    Product orange("Orange", 3);

    // Создаем магазины
    Shop shop1("Fruit Shop", 1);
    shop1.addProduct(ProductInfo(apple, 1.0, 100));
    shop1.addProduct(ProductInfo(banana, 0.5, 50));

    Shop shop2("Grocery Store", 2);
    shop2.addProduct(ProductInfo(apple, 0.8, 80));
    shop2.addProduct(ProductInfo(orange, 1.2, 30));

    // Добавляем магазины в менеджер
    manager.addShop(shop1);
    manager.addShop(shop2);

    // Регистрация покупателя
    Buyer buyer("John Doe", 1, 10.0);

    // Покупка товаров
    buyer.purchase(apple, 2, shop1);
    buyer.purchase(banana, 3, shop2);

    // Поиск магазина с самой низкой ценой на продукт
    Shop cheapestShop = manager.findCheapestShop(apple);
    std::cout << "Cheapest shop for " << apple.getTitle() << " is " << cheapestShop.getTitle() << std::endl;

    // Список всех магазинов
    std::cout << "Available shops:" << std::endl;
    manager.listAllShops();

    return 0;
}