#pragma once
#include <iostream>
#include <string>

class SymString {
private:
    std::string id;
    std::string value;

public:
    SymString(const std::string& id = "noname", const std::string& val = "");
    SymString(const SymString& other);
    ~SymString();

    std::string getId() const { return id; }
    std::string getValue() const { return value; }
    bool setId(const std::string& newId);
    bool setValue(const std::string& newVal);

    void Read();
    void Show() const;

    SymString& operator=(const SymString& other);
    operator std::string() const;

    friend SymString operator+(const SymString& s1, const SymString& s2);
    friend std::ostream& operator<<(std::ostream& out, const SymString& s);
    friend std::istream& operator>>(std::istream& in, SymString& s);
};