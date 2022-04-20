#include "Passenger.h"

Passenger::Passenger(std::string firstname, std::string lastname) {
    this->firstname = firstname;
    this->lastname = lastname;
}

const std::string &Passenger::getFirstname() const {
    return firstname;
}

const std::string &Passenger::getLastname() const {
    return lastname;
}

bool Passenger::operator<(const Passenger &rhs) const {
    int l = 0;
    int fl = 0;
    while (l < this->lastname.length()) {
        if (this->lastname.at(l) < rhs.lastname.at(l))
            return true;
        else if (this->lastname.at(l) == rhs.lastname.at(l))
            l++;
        else
            return false;
    }
    if (this->lastname.length() < rhs.lastname.length())
        return true;
    else if (this->lastname == rhs.lastname) {
        while (fl < this->firstname.length()) {
            if (this->firstname.at(fl) < rhs.firstname.at(fl))
                return true;
            else if (this->firstname.at(fl) == rhs.firstname.at(fl))
                fl++;
            else
                return false;
        }
    }
    else
        return false;
    
}

bool Passenger::operator>(const Passenger &rhs) const {
    return rhs < *this;
}

bool Passenger::operator==(const Passenger &rhs) const {
    return firstname == rhs.firstname && lastname == rhs.lastname;
}

bool Passenger::operator!=(const Passenger &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Passenger &passenger) {
    os << "Passenger(firstname: " << passenger.firstname;
    os << ", lastname: " << passenger.lastname << ")";
    return os;
}
