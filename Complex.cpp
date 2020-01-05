//
// Created by Андрей Москалёв on 12.12.2019.
//

#include "Complex.h"

Complex::Complex(double r, double i) {
    this->real = r;
    this->imag = i;
}

Complex::Complex() {
    this->real = 0;
    this->imag = 0;
}

Complex Complex::operator+(Complex const &obj) const {
    return {real + obj.real, imag + obj.imag};
}

Complex Complex::operator-(Complex const &obj) const {
    return {real - obj.real, imag - obj.imag};
}

Complex Complex::operator*(Complex const &obj) const {
    return {real * obj.real - imag * obj.imag, real * obj.imag + imag * obj.real};
}


Complex Complex::operator/(Complex const &obj) const {
    return {(real * obj.real + imag * obj.imag) / (obj.real * obj.real + obj.imag * obj.imag),
            (imag * obj.real - real * obj.imag) / (obj.real * obj.real + obj.imag * obj.imag)};
}

double Complex::pointRadius() {
    return sqrt(real * real + imag * imag);
}
