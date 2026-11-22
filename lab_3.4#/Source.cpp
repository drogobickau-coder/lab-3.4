#include <iostream>
#include <limits>
#include <string>
#include "Factory.h"
#pragma execution_character_set("utf-8")

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

void printMenu() {
    std::cout << "\n================ МЕНЮ (Варіант 17) ================\n"
        << "1. Створити об'єкт SymString (через operator>>)\n"
        << "2. Створити об'єкт DecString (через operator>>)\n"
        << "3. Видалити об'єкт SymString\n"
        << "4. Видалити об'єкт DecString\n"
        << "5. Показати всі об'єкти (через operator<<)\n"
        << "6. Показати значення конкретного об'єкта\n"
        << "7. Показати Hex-значення об'єкта DecString (ShowHex)\n"
        << "8. Додати два об'єкти SymString (operator+, конкатенація)\n"
        << "9. Додати два об'єкти DecString (operator+, чисельна сума)\n"
        << "0. Вихід\n"
        << "===================================================\n"
        << "Оберіть дію: ";
}

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    {
        setlocale(LC_ALL, "uk_UA.UTF-8");
    }
#endif

    Factory factory;
    int choice = -1;

    // Початкові тестові об'єкти
    factory.createSymString("s1", "Hello, ");
    factory.createSymString("s2", "OOP!");
    factory.createDecString("d1", "255");
    factory.createDecString("d2", "45");

    do {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некоректне введення. Введіть число від 0 до 9.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            if (SymString* created = factory.createSymString()) {
                std::cout << "Створено: " << *created << std::endl;
            }
            break;
        }
        case 2: {
            if (DecString* created = factory.createDecString()) {
                std::cout << "Створено: " << *created << std::endl;
            }
            break;
        }
        case 3: {
            std::string id;
            std::cout << "Введіть ID об'єкта SymString для видалення: ";
            std::getline(std::cin, id);
            if (factory.deleteSymString(id)) {
                std::cout << "Об'єкт SymString видалено.\n";
            }
            else {
                std::cout << "Об'єкт з таким ID не знайдено.\n";
            }
            break;
        }
        case 4: {
            std::string id;
            std::cout << "Введіть ID об'єкта DecString для видалення: ";
            std::getline(std::cin, id);
            if (factory.deleteDecString(id)) {
                std::cout << "Об'єкт DecString видалено.\n";
            }
            else {
                std::cout << "Об'єкт з таким ID не знайдено.\n";
            }
            break;
        }
        case 5: {
            factory.showAll();
            break;
        }
        case 6: {
            int type = 0;
            std::string id;
            std::cout << "Тип об'єкта (1 - SymString, 2 - DecString): ";
            std::cin >> type;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введіть ID: ";
            std::getline(std::cin, id);

            if (type == 1) {
                if (SymString* s = factory.findSymString(id)) {
                    std::cout << *s << std::endl;
                }
                else {
                    std::cout << "SymString не знайдено.\n";
                }
            }
            else if (type == 2) {
                if (DecString* d = factory.findDecString(id)) {
                    std::cout << *d << std::endl;
                }
                else {
                    std::cout << "DecString не знайдено.\n";
                }
            }
            else {
                std::cout << "Невірний тип.\n";
            }
            break;
        }
        case 7: {
            std::string id;
            std::cout << "Введіть ID об'єкта DecString: ";
            std::getline(std::cin, id);
            if (DecString* d = factory.findDecString(id)) {
                d->ShowHex();
            }
            else {
                std::cout << "DecString з таким ID не знайдено.\n";
            }
            break;
        }
        case 8: {
            std::string id1, id2;
            std::cout << "Введіть ID першого SymString: ";
            std::getline(std::cin, id1);
            std::cout << "Введіть ID другого SymString: ";
            std::getline(std::cin, id2);

            SymString* s1 = factory.findSymString(id1);
            SymString* s2 = factory.findSymString(id2);
            if (s1 && s2) {
                SymString res = (*s1) + (*s2);
                std::cout << "Результат конкатенації: " << res << std::endl;
            }
            else {
                std::cout << "Один або обидва об'єкти не знайдено.\n";
            }
            break;
        }
        case 9: {
            std::string id1, id2;
            std::cout << "Введіть ID першого DecString: ";
            std::getline(std::cin, id1);
            std::cout << "Введіть ID другого DecString: ";
            std::getline(std::cin, id2);

            DecString* d1 = factory.findDecString(id1);
            DecString* d2 = factory.findDecString(id2);
            if (d1 && d2) {
                DecString res = (*d1) + (*d2);
                std::cout << "Результат додавання: " << res << std::endl;
                res.ShowHex();
            }
            else {
                std::cout << "Один або обидва об'єкти не знайдено.\n";
            }
            break;
        }
        case 0:
            std::cout << "Завершення роботи програми.\n";
            break;
        default:
            std::cout << "Невідомий пункт меню.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}