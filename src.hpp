#include <iostream>     // 输入输出
#include <stdexcept>    // 异常处理
// 你不可以使用任何其他的头文件!

// 下发异常类。你不需要修改这个类。
struct divided_by_zero final : std::exception {
public:
    divided_by_zero()   = default;
    ~divided_by_zero()  = default;
    const char *what() const noexcept override { return "Divided by zero!"; };
};

template <typename _Tp>
struct fraction {
private:
    _Tp numerator;
    _Tp denominator;
    
    // Helper function to simplify fraction
    void simplify() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        
        _Tp abs_num = numerator < 0 ? -numerator : numerator;
        _Tp abs_den = denominator < 0 ? -denominator : denominator;
        
        _Tp common_divisor = gcd(abs_num, abs_den);
        if (common_divisor != 0 && common_divisor != 1) {
            numerator /= common_divisor;
            denominator /= common_divisor;
        }
    }
    
    // GCD function
    static _Tp gcd(_Tp x, _Tp y) {
        while (y) {
            x %= y;
            std::swap(x, y);
        }
        return x;
    }
    
    // Fast power function
    static _Tp fast_pow(_Tp x, long long y) {
        _Tp res = 1;
        while (y) {
            if (y & 1) res *= x;
            x *= x;
            y >>= 1;
        }
        return res;
    }

public:
    fraction() : numerator(0), denominator(1) {}
    
    fraction(_Tp x) : numerator(x), denominator(1) {}
    
    fraction(_Tp x, _Tp y) : numerator(x), denominator(y) {
        simplify();
    }
    
    fraction operator + (const fraction &other) const {
        _Tp new_num = numerator * other.denominator + other.numerator * denominator;
        _Tp new_den = denominator * other.denominator;
        return fraction(new_num, new_den);
    }
    
    fraction operator - (const fraction &other) const {
        _Tp new_num = numerator * other.denominator - other.numerator * denominator;
        _Tp new_den = denominator * other.denominator;
        return fraction(new_num, new_den);
    }
    
    fraction operator * (const fraction &other) const {
        _Tp new_num = numerator * other.numerator;
        _Tp new_den = denominator * other.denominator;
        return fraction(new_num, new_den);
    }
    
    fraction operator / (const fraction &other) const {
        if (other.numerator == 0) {
            throw divided_by_zero();
        }
        _Tp new_num = numerator * other.denominator;
        _Tp new_den = denominator * other.numerator;
        return fraction(new_num, new_den);
    }
    
    fraction operator ^ (long long exp) const {
        if (exp < 0) {
            if (numerator == 0) {
                throw divided_by_zero();
            }
            _Tp new_num = fast_pow(denominator, -exp);
            _Tp new_den = fast_pow(numerator, -exp);
            return fraction(new_num, new_den);
        } else {
            _Tp new_num = fast_pow(numerator, exp);
            _Tp new_den = fast_pow(denominator, exp);
            return fraction(new_num, new_den);
        }
    }
    
    fraction &operator += (const fraction &other) {
        *this = *this + other;
        return *this;
    }
    
    fraction &operator -= (const fraction &other) {
        *this = *this - other;
        return *this;
    }
    
    fraction &operator *= (const fraction &other) {
        *this = *this * other;
        return *this;
    }
    
    fraction &operator /= (const fraction &other) {
        *this = *this / other;
        return *this;
    }
    
    fraction &operator ^= (long long exp) {
        *this = *this ^ exp;
        return *this;
    }
    
    explicit operator double() const {
        return static_cast<double>(numerator) / static_cast<double>(denominator);
    }
    
    explicit operator bool() const {
        return numerator != 0;
    }
    
    friend bool operator == (const fraction &a, const fraction &b) {
        return a.numerator == b.numerator && a.denominator == b.denominator;
    }
    
    friend bool operator < (const fraction &a, const fraction &b) {
        return a.numerator * b.denominator < b.numerator * a.denominator;
    }
    
    friend std::ostream & operator << (std::ostream &os, const fraction &f) {
        os << f.numerator << "/" << f.denominator;
        return os;
    }
};