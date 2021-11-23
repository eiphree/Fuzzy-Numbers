/* 
    Rozwiązanie trzeciego zadania zaliczeniowego
    Agnieszka Pałka 406275
    Wiktor Chmielewski 429131
*/

#include <cmath>
#include "fuzzy.h"
using namespace std;

/* TriFuzzyNum */

// porównywanie 

namespace {
    using rank = tuple<real_t, real_t, real_t>;

    constexpr rank getRank(const TriFuzzyNum& tfn) {
        real_t z = (tfn.upper_value() - tfn.lower_value()) 
            + sqrt(1 + (tfn.upper_value() - tfn.modal_value()) 
            * (tfn.upper_value() - tfn.modal_value())) 
            + sqrt(1 + (tfn.modal_value() - tfn.lower_value()) 
            * (tfn.modal_value() - tfn.lower_value()));
        real_t y = (tfn.upper_value() - tfn.lower_value()) / z;
        real_t x = ((tfn.upper_value() - tfn.lower_value()) * tfn.modal_value() 
            + sqrt(1 + (tfn.upper_value() - tfn.modal_value()) * 
            (tfn.upper_value() - tfn.modal_value())) * tfn.lower_value() + 
            sqrt(1 + (tfn.modal_value() - tfn.lower_value()) 
            * (tfn.modal_value() - tfn.lower_value())) * tfn.upper_value()) / z;
        return make_tuple(x - y / 2, 1 - y, tfn.modal_value());
    }
}

int TriFuzzyNum::operator<=>(const TriFuzzyNum& that) const {
    auto res = (getRank(*this) <=> getRank(that));
    if (res > 0) return 1;
    else if (res < 0) return -1;
    else return 0;
}

// wypisywanie

ostream& operator<<(ostream& os, const TriFuzzyNum& tfn) {
    os << "(" << tfn.lower_value() << ", " << 
        tfn.modal_value() << ", " << tfn.upper_value() << ")";
    return os;
}

/* TriFuzzyNumSet */

// wstawianie

void TriFuzzyNumSet::insert(const TriFuzzyNum& tfn) {
    vec.push_back(tfn);
}

void TriFuzzyNumSet::insert(TriFuzzyNum&& tfn) {
    vec.push_back(move(tfn));
}

// usuwanie

void TriFuzzyNumSet::remove(const TriFuzzyNum& tfn) {
    for (auto it = vec.begin(); it != vec.end(); it++) {
        if (*it == tfn) {
            vec.erase(it);
            return;
        }
    }
}

// średnia arytmetyczna

TriFuzzyNum TriFuzzyNumSet::arithmetic_mean() {
    if (vec.empty()) {
        throw length_error("TriFuzzyNumSet::arithmetic_mean - the set is empty.");
    }
    real_t l = 0, m = 0, u = 0;
    for (size_t i = 0; i < vec.size(); i++) {
        l += vec[i].lower_value();
        m += vec[i].modal_value();
        u += vec[i].upper_value();
    }
    l /= vec.size();
    m /= vec.size();
    u /= vec.size();
    return TriFuzzyNum(l, m, u);
}

