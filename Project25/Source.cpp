#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

struct Product {
	string name;
	int quantity;
	double price;
};

void writeToFile(const string& filename, const vector & products) {
	ofstream file(filename);
    if (file.is_open()) {
        for (const Product& product : products) {
            file << product.name << " " << product.quantity << " " << product.price ;
        }

        file.close();
        std::cout << "Data has been written to file: " << filename ;
    }
    else {
        std::cout << "Error opening file!"  ;
    }
}

vector readFromFile(const string& filename) {
    vector products;
    ifstream file(filename);
    if (file.is_open()) {
        Product product;
        while (file >> product.name >> product.quantity >> product.price) {
            products.push_back(product);
        }

        file.close();
        std::cout << "Данные были считаны из файла: " << filename  ;
    }
    else {
        std::cout << "Error 404!"  ;
    }

    return products;
}

void printTable(const vector& products) {
    std::cout << "Bvz\t\tколичество\tЦена"  ;
    std::cout << "----------------------------------" ;
    for (const Product& product : products) {
        std::cout << product.name << "\t\t" << product.quantity << "\t\t" << product.price  ;
    }
}

int main() {
    vector products;
    string filename;
    while (true) {
        std::cout << "Файл для работы (1, 2 or 3) или войти 'q' Сброс: ";
        char choice;
        std::cin >> choice;

        if (choice == 'q') {
            break;
        }

        filename = "file" + to_string(choice) + ".txt";

        if (ifstream(filename)) {
            cout << "Файл " << filename << " Имя уже есть." << endl;
            cout << "Вы хотите не заполнять его? (y/n): ";
            char skip;
            cin >> skip;

            if (skip == 'y') {
                products = readFromFile(filename);
            }
            else {
                Product product;
                cout << "Введите название продукта, количество и цену: ";
                cin >> product.name >> product.quantity >> product.price;

                products.push_back(product);

                writeToFile(filename, products);
            }
        }
        else {
             
            Product product;
            cout << "Введите название продукта, количество и цену: ";
            cin >> product.name >> product.quantity >> product.price;

            products.push_back(product);

            writeToFile(filename, products);
        }
    }

    printTable(products);

    return 0;
}

