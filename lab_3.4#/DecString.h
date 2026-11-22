#pragma once
#include "SymString.h"

class DecString : public SymString {
public:
    static bool isValidDec(const std::string& val);

    DecString(const std::string& id = "noname", const std::string& val = "0");
    DecString(const DecString& other);
    ~DecString();

    bool setValue(const std::string& newVal);

    void Read();
    void Show() const;
    std::string toHex() const;
    void ShowHex() const;

    DecString& operator=(const DecString& other);
    operator std::string() const;

    friend DecString operator+(const DecString& s1, const DecString& s2);
    friend std::ostream& operator<<(std::ostream& out, const DecString& s);
    friend std::istream& operator>>(std::istream& in, DecString& s);
};