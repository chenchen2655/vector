#include <iostream>
#include <cmath> 
using namespace std;
template<typename T> class Complex 
{
private:
    T real_;
    T imag_;
    T modulus_ = sqrt( pow(real_, 2) + pow(imag_, 2) );
public:
	Complex() : real_(0), imag_(0) {}
    Complex(T real, T imag) : real_(real), imag_(imag) {}
    
    T real() const { return real_; }
    T imag() const { return imag_; }
    T modulus() const { return modulus_; }
    Complex<T> operator-() const { return Complex<T>(-real_, -imag_); } //ȡ�����㣬ʵ���鲿�ֱ�ȡ�� 
    
    // Binary operators
    Complex<T> operator+(const Complex<T>& other) const { //�ӷ����㣬ʵ���鲿�ֱ���� 
        return Complex<T>(real_ + other.real_, imag_ + other.imag_);
    }
    
    Complex<T> operator-(const Complex<T>& other) const { //�������㣬ʵ���鲿�ֱ���� 
        return Complex<T>(real_ - other.real_, imag_ - other.imag_);
	}
    
    Complex<T> operator*(const Complex<T>& other) const { //�˷����㣬��z1=a+bi��z2=c+di(a��b��c��d��R)������������������ô���ǵĻ�(a+bi)(c+di)=(ac-bd)+(bc+ad)i�� 
        return Complex<T>(real_ * other.real_ - imag_ * other.imag_, 
                          real_ * other.imag_ + imag_ * other.real_);
    }
    
    Complex<T> operator/(const Complex<T>& other) const { //�������㣬����(c+di)(x+yi)=(a+bi)�ĸ���x+yi(x,y��R)�и���a+bi���Ը���c+di���̡� 
        T divisor = other.real_ * other.real_ + other.imag_ * other.imag_;
        return Complex<T>((real_ * other.real_ + imag_ * other.imag_) / divisor, 
                          (imag_ * other.real_ - real_ * other.imag_) / divisor);
    }
    
    bool operator==(const Complex<T>& other) const { //�е����㣬ʵ���鲿����ȸ�������� 
        return real_ == other.real_ && imag_ == other.imag_;
    }
    
    bool operator!=(const Complex<T>& other) const { //�зǵ����� 
        return !(*this == other);
    }
    
    bool operator<(const Complex<T>& other) const { //��С�����㣨��ģ��С���� 
		if(modulus_ < other.modulus_)
			return modulus_ < other.modulus_;
		else if(modulus_ == other.modulus_)
			return real_ < other.real_;
	}
	
	bool operator>(const Complex<T>& other) const { //�д������㣨��ģ��С���� ��������Ǵ��ڷǵ��ڼ�С�ڵ��뷨 
		if(modulus_ > other.modulus_)
			return modulus_> other.modulus_;
		else if(modulus_ == other.modulus_)
			return real_ > other.real_;
	}
    
	void ComPrint () const { //��ӡ���� 
		cout<<real_<<"+"<<imag_<<"i"<<endl;
	} 
};
