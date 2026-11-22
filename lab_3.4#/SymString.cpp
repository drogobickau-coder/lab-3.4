#include "SymString.h"
#include <sstream>
#pragma execution_character_set("utf-8")

SymString::SymString(const std::string& id, const std::string& val) {
    if (!setId(id)) {
        this->id = "noname";
    }
    setValue(val);
}

SymString::SymString(const SymString& other) {
    setId(other.getId());
    setValue(other.getValue());
}

SymString::~SymString() {}

bool SymString::setId(const std::string& newId) {
    if (newId.empty()) {
        std::cerr << "Помилка: ідентифікатор не може бути порожнім.\n";
        return false;
    }
    id = newId;
    return true;
}

bool SymString::setValue(const std::string& newVal) {
    value = newVal;
    return true;
}

void SymString::Read() {
    std::cin >> *this;
}

void SymString::Show() const {
    std::cout << *this << std::endl;
}

SymString& SymString::operator=(const SymString& other) {
    if (this != &other) {
        setId(other.getId());
        setValue(other.getValue());
    }
    return *this;
}

SymString::operator std::string() const {
    std::stringstream ss;
    ss << "[SymString] ID: \"" << getId()
        << "\" | Значення: \"" << getValue() << "\"";
    return ss.str();
}

// Конкатенація двох символьних рядків
SymString operator+(const SymString& s1, const SymString& s2) {
    return SymString(s1.getId() + "+" + s2.getId(), s1.getValue() + s2.getValue());
}

std::ostream& operator<<(std::ostream& out, const SymString& s) {
    out << std::string(s);
    return out;
}

std::istream& operator>>(std::istream& in, SymString& s) {
    std::string newId, newVal;
    do {
        std::cout << "Введіть ID для SymString: ";
        if (!std::getline(in, newId)) {
            return in;
        }
    } while (!s.setId(newId));

    std::cout << "Введіть символьний рядок: ";
    if (std::getline(in, newVal)) {
        s.setValue(newVal);
    }
    return in;
}