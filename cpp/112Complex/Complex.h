#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <cmath>
#include <iostream>
class ostream;
class Complex;

Complex &__doapl(Complex* ths,const Complex& r);

class Complex
{
public:
	Complex(double r=0,double i=0):re(r),im(i){};
	Complex &operator += (const Complex&);
	double real () const {return re;}
	double imag () const {return im;}
private:
	double re,im;
	friend Complex &__doapl(Complex*,const Complex&);
};
inline Complex& __doapl(Complex* ths,const Complex& r)
{
	ths->re += r.re;
	ths->im += r.im;
	return *ths;
}
inline double real (const Complex& x)
{
	return x.real();
}
inline double imag (const Complex& x)
{
	return x.imag();
}
inline Complex& Complex::operator += (const Complex& r)
{
	return __doapl(this, r);
}
inline std::ostream & operator <<(std::ostream &os, const Complex& x)
{
	return os << '(' <<real(x)<<','<<imag(x) << ')';
}
inline Complex operator + (const Complex& x,const Complex& y)
{
	return Complex(real(x)+real(y),imag(x)+imag(y));
}
inline Complex operator + (const double& x,const Complex& y)
{
	return Complex(x+real(y),imag(y));
}
inline Complex operator + (const Complex& x,const double y)
{
	return Complex(real(x)+y,imag(x));
}
#endif /*_COMPLEX_H_*/
