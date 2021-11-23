/* 
    Rozwiązanie trzeciego zadania zaliczeniowego
    Agnieszka Pałka 406275
    Wiktor Chmielewski 429131
*/

#ifndef FUZZY_H
#define FUZZY_H

#include <iostream>
#include <algorithm>
#include <vector>

using real_t = double;

class TriFuzzyNum {
    private:
        real_t l, u, m;
    public: 
        // konstruktory 
        constexpr TriFuzzyNum(real_t x, real_t y, real_t z) :
            l(std::min({x, y, z})),
            u(std::max({x, y, z})),
            m(x + y + z - l - u)
        { };
        constexpr TriFuzzyNum(const TriFuzzyNum&) = default;
        constexpr TriFuzzyNum(TriFuzzyNum&&) = default;
        // odczytywanie wartości
        constexpr real_t lower_value() const { return l; }
        constexpr real_t modal_value() const { return m; }
        constexpr real_t upper_value() const { return u; }
        // operacje przypisania
        constexpr TriFuzzyNum& operator=(const TriFuzzyNum&) = default;
        constexpr TriFuzzyNum& operator=(TriFuzzyNum&&) = default;
        // operacje arytmetyczne
        constexpr TriFuzzyNum& operator+=(const TriFuzzyNum&);
        constexpr TriFuzzyNum& operator-=(const TriFuzzyNum&);
        constexpr TriFuzzyNum& operator*=(const TriFuzzyNum&);
        // operacje porównania
        int operator<=>(const TriFuzzyNum&) const;
        // operacje porównania parametrów
        constexpr bool operator==(const TriFuzzyNum&) const;
        constexpr bool operator!=(const TriFuzzyNum&) const;
};

class TriFuzzyNumSet {
    private:
        std::vector<TriFuzzyNum> vec;
    public:
        // konstruktory
        TriFuzzyNumSet() : vec() { };
        TriFuzzyNumSet(std::initializer_list<TriFuzzyNum> s) : vec(s) { };
        TriFuzzyNumSet(const TriFuzzyNumSet& that) = default;
        TriFuzzyNumSet(TriFuzzyNumSet&& that) = default;
        // operacje przypisania
        TriFuzzyNumSet& operator=(const TriFuzzyNumSet&) = default;
        TriFuzzyNumSet& operator=(TriFuzzyNumSet&&) = default;
        // wstawianie
        void insert(const TriFuzzyNum&);
        void insert(TriFuzzyNum&&);
        // usuwanie
        void remove(const TriFuzzyNum&);
        // średnia arytmetyczna
        TriFuzzyNum arithmetic_mean();
};

// wypisywanie
std::ostream& operator<<(std::ostream&, const TriFuzzyNum&);

// operacje arytmetyczne

constexpr TriFuzzyNum& TriFuzzyNum::operator+=(const TriFuzzyNum& that) {
    real_t x = l + that.l;
    real_t y = m + that.m;
    real_t z = u + that.u;
    l = std::min({x, y, z});
    u = std::max({x, y, z});
    m = x + y + z - l - u;
    return *this;
}

constexpr const TriFuzzyNum operator+(const TriFuzzyNum& a, const TriFuzzyNum& b) {
    return TriFuzzyNum(a) += b;
}

constexpr TriFuzzyNum& TriFuzzyNum::operator-=(const TriFuzzyNum& that) {
    real_t x = l - that.u;
    real_t y = m - that.m;
    real_t z = u - that.l;
    l = std::min({x, y, z});
    u = std::max({x, y, z});
    m = x + y + z - l - u;
    return *this;
}

constexpr const TriFuzzyNum operator-(const TriFuzzyNum& a, const TriFuzzyNum& b) {
    return TriFuzzyNum(a) -= b;
}

constexpr TriFuzzyNum& TriFuzzyNum::operator*=(const TriFuzzyNum& that) {
    real_t x = l * that.l;
    real_t y = m * that.m;
    real_t z = u * that.u;
    l = std::min({x, y, z});
    u = std::max({x, y, z});
    m = x + y + z - l - u;
    return *this;
}

constexpr const TriFuzzyNum operator*(const TriFuzzyNum& a, const TriFuzzyNum& b) {
    return TriFuzzyNum(a) *= b;
}

// operacje porównania parametrów

constexpr bool TriFuzzyNum::operator==(const TriFuzzyNum& that) const {
    return l == that.l && m == that.m && u == that.u;
}

constexpr bool TriFuzzyNum::operator!=(const TriFuzzyNum& that) const {
    return !(*this == that);
}

// crisp numbers
consteval TriFuzzyNum crisp_number(real_t v) {
    return TriFuzzyNum(v, v, v);
}

constinit const TriFuzzyNum crisp_zero = crisp_number(0);

#endif /* FUZZY_H */
