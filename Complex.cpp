//
// Created by noaml on 30/06/2024.
//
// ID: 326662574
// MAIL: noamlevin11@gmail.com

#include "Complex.hpp"

Complex::Complex(double real, double imag) : real(real), imag(imag) {}

double Complex::normalize() const {
    return sqrt(pow(this->real, 2) + pow(this->imag, 2));
}

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.to_string();
    return os;
}

string Complex::to_string() const {
    stringstream ss;
    ss << this->real << (this->imag >= 0 ? "+" : "") << this->imag << "i";
    return ss.str();
}