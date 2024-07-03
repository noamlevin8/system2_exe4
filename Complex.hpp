//
// Created by noaml on 30/06/2024.
//
// ID: 326662574
// MAIL: noamlevin11@gmail.com

#pragma once

#include <cmath>
#include <sstream>
#include <iostream>
#include <ostream>

using namespace std;

class Complex {
    private:
            double real;
            double imag;

            double normalize() const;

    public:
            Complex(double real = 0, double imag = 0); // Constructor

            // Getters
            inline double getReal() const { return this->real; }
            inline double getImag() const { return this->imag; }

            // Setters
            inline void setReal(double value) { this->real = value; }
            inline void setImag(double value) { this->imag = value; }

            // Operators "==" and "<" overload
            inline bool operator==(const Complex& other) const { return normalize() == other.normalize(); }
            inline bool operator<(const Complex& other) const { return normalize() < other.normalize(); }

            friend ostream& operator<<(ostream& os, const Complex& c); // Operator "<<"

            string to_string() const; // Override for "to_string"
};
