#include <stdio.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

long long gcd(long long a, long long b) {
    long long temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Fraction sum_of_inverse_of_divisors(int n) {
    Fraction result = {0, 1};
    if (n <= 0) {
        return result;
    }
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            int div1 = i;
            int div2 = n / i;
            
            result.num = result.num * div1 + result.den;
            result.den *= div1;
            
            long long common = gcd(result.num, result.den);
            result.num /= common;
            result.den /= common;

            if (div1 != div2) {
                result.num = result.num * div2 + result.den;
                result.den *= div2;
                
                common = gcd(result.num, result.den);
                result.num /= common;
                result.den /= common;
            }
        }
    }
    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    Fraction res = sum_of_inverse_of_divisors(n);
    printf("%lld/%lld\n", res.num, res.den);
    return 0;
}