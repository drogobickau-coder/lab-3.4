#include "DecString.h"
#include <cctype>
#include <sstream>
#include <stdexcept>
#pragma execution_character_set("utf-8")

bool DecString::isValidDec(const std::string& val) {
    if (val.empty()) {
        return false;
    }
    for (char ch : val) {
        if (!std::isdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    try {
        (void)std::stoull(val);
    }
    catch (const std::out_of_range&) {
        return false;
    }
    return true;
}

DecString::DecString(const std::string& id, const std::string& val)
    : SymString(id, "0") {
    if (!setValue(val)) {
        SymString::setValue("0");
    }
}

DecString::DecString(const DecString& other)
    : SymString(other) {
    setValue(other.getValue());
}

DecString::~DecString() {}

bool DecString::setValue(const std::string& newVal) {
    if (!isValidDec(newVal)) {
        std::cerr << "Помилка: \"" << newVal
            << "\" не є коректним додатним десятковим числом.\n";
        return false;
    }
    unsigned long long num = std::stoull(newVal);
    return SymString::setValue(std::to_string(num));
}

void DecString::Read() {
    std::cin >> *this;
}

void DecString::Show() const {
    std::cout << *this << std::endl;
}

std::string DecString::toHex() const {
    unsigned long long num = std::stoull(getValue());
    std::stringstream ss;
    ss << std::uppercase << std::hex << num;
    return ss.str();
}

void DecString::ShowHex() const {
    std::cout << *this << " | Значення (Hex): 0x" << toHex() << std::endl;
}

DecString& DecString::operator=(const DecString& other) {
    if (this != &other) {
        SymString::operator=(other); // явний виклик базової операції присвоєння
        setValue(other.getValue());
    }
    return *this;
}

DecString::operator std::string() const {
    std::stringstream ss;
    ss << "[DecString] ID: \"" << getId()
        << "\" | Значення (Dec): " << getValue();
    return ss.str();
}

// Чисельне додавання двох десяткових рядків з перетворенням до DecString
DecString operator+(const DecString& s1, const DecString& s2) {
    unsigned long long a = std::stoull(s1.getValue());
    unsigned long long b = std::stoull(s2.getValue());
    return DecString(s1.getId() + "+" + s2.getId(), std::to_string(a + b));
}

std::ostream& operator<<(std::ostream& out, const DecString& s) {
    out << std::string(s);
    return out;
}

std::istream& operator>>(std::istream& in, DecString& s) {
    std::string newId, newVal;
    do {
        std::cout << "Введіть ID для DecString: ";
        if (!std::getline(in, newId)) {
            return in;
        }
    } while (!s.setId(newId));

    do {
        std::cout << "Введіть додатне десяткове число: ";
        if (!std::getline(in, newVal)) {
            return in;
        }
    } while (!s.setValue(newVal));

    return in;
}