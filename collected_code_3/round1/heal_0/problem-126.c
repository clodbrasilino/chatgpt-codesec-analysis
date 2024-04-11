#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int sumCommonDivisors(int a, int b) {
    int n = gcd(a, b);
    int result = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (n / i == i)
                result += i;
            else
                result += (i + n / i);
        }
    }
    return result;
}

int main() {
    int a = 10, b = 15;
    printf("Sum of common divisors is %d", sumCommonDivisors(a, b));
    return 0;
}