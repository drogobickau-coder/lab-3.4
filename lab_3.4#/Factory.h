#pragma once
#include <vector>
#include <string>
#include "SymString.h"
#include "DecString.h"

class Factory {
private:
    std::vector<SymString*> symObjects;
    std::vector<DecString*> decObjects;

public:
    Factory() = default;
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;
    ~Factory();

    SymString* createSymString(const std::string& id, const std::string& val);
    SymString* createSymString(); // створення через оператор введення >>

    DecString* createDecString(const std::string& id, const std::string& val);
    DecString* createDecString(); // створення через оператор введення >>

    bool deleteSymString(const std::string& id);
    bool deleteDecString(const std::string& id);

    SymString* findSymString(const std::string& id) const;
    DecString* findDecString(const std::string& id) const;

    void showAllSymStrings() const;
    void showAllDecStrings() const;
    void showAll() const;
};