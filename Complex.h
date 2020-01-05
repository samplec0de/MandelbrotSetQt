//
// Created by Андрей Москалёв on 12.12.2019.
//

#ifndef MANDELBROT_COMPLEX_H
#define MANDELBROT_COMPLEX_H
#include <cmath>

class Complex {
public:
    double real, imag;
    Complex(double r, double i);
    Complex();
    Complex operator+(Complex const &obj) const;
    Complex operator-(Complex const &obj) const;
    Complex operator*(Complex const &obj) const;
    Complex operator/(Complex const &obj) const;
    double pointRadius();
};


#endif //MANDELBROT_COMPLEX_H
