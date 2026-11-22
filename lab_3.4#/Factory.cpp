#include "Factory.h"
#include <iostream>
#pragma execution_character_set("utf-8")

Factory::~Factory() {
    for (SymString* obj : symObjects) {
        delete obj;
    }
    for (DecString* obj : decObjects) {
        delete obj;
    }
}

SymString* Factory::createSymString(const std::string& id, const std::string& val) {
    if (id.empty() || findSymString(id) != nullptr) {
        std::cerr << "Помилка: ідентифікатор порожній або вже існує серед SymString.\n";
        return nullptr;
    }
    SymString* obj = new SymString(id, val);
    symObjects.push_back(obj);
    return obj;
}

SymString* Factory::createSymString() {
    SymString* obj = new SymString();
    std::cin >> *obj;
    if (findSymString(obj->getId()) != nullptr) {
        std::cerr << "Помилка: об'єкт SymString з ID \"" << obj->getId() << "\" вже існує.\n";
        delete obj;
        return nullptr;
    }
    symObjects.push_back(obj);
    return obj;
}

DecString* Factory::createDecString(const std::string& id, const std::string& val) {
    if (id.empty() || findDecString(id) != nullptr) {
        std::cerr << "Помилка: ідентифікатор порожній або вже існує серед DecString.\n";
        return nullptr;
    }
    if (!DecString::isValidDec(val)) {
        std::cerr << "Помилка: значення \"" << val
            << "\" має містити лише десяткові цифри.\n";
        return nullptr;
    }
    DecString* obj = new DecString(id, val);
    decObjects.push_back(obj);
    return obj;
}

DecString* Factory::createDecString() {
    DecString* obj = new DecString();
    std::cin >> *obj;
    if (findDecString(obj->getId()) != nullptr) {
        std::cerr << "Помилка: об'єкт DecString з ID \"" << obj->getId() << "\" вже існує.\n";
        delete obj;
        return nullptr;
    }
    decObjects.push_back(obj);
    return obj;
}

bool Factory::deleteSymString(const std::string& id) {
    for (auto it = symObjects.begin(); it != symObjects.end(); ++it) {
        if ((*it)->getId() == id) {
            delete* it;
            symObjects.erase(it);
            return true;
        }
    }
    return false;
}

bool Factory::deleteDecString(const std::string& id) {
    for (auto it = decObjects.begin(); it != decObjects.end(); ++it) {
        if ((*it)->getId() == id) {
            delete* it;
            decObjects.erase(it);
            return true;
        }
    }
    return false;
}

SymString* Factory::findSymString(const std::string& id) const {
    for (SymString* obj : symObjects) {
        if (obj->getId() == id) {
            return obj;
        }
    }
    return nullptr;
}

DecString* Factory::findDecString(const std::string& id) const {
    for (DecString* obj : decObjects) {
        if (obj->getId() == id) {
            return obj;
        }
    }
    return nullptr;
}

void Factory::showAllSymStrings() const {
    std::cout << "--- Об'єкти SymString ---\n";
    if (symObjects.empty()) {
        std::cout << "  (список порожній)\n";
        return;
    }
    for (const SymString* obj : symObjects) {
        std::cout << *obj << std::endl;
    }
}

void Factory::showAllDecStrings() const {
    std::cout << "--- Об'єкти DecString ---\n";
    if (decObjects.empty()) {
        std::cout << "  (список порожній)\n";
        return;
    }
    for (const DecString* obj : decObjects) {
        std::cout << *obj << std::endl;
    }
}

void Factory::showAll() const {
    showAllSymStrings();
    showAllDecStrings();
}