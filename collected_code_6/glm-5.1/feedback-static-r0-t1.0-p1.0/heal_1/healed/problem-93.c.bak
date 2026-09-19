#include <stdio.h>
#include <stdlib.h>

long long power(int a, int b) {
    if (a == 0 && b <= 0) {
        return 0;
    }
    long long result = 1;
    long long base = a;
    int exp = b;
    if (exp < 0) {
        base = 1 / base;
        exp = -exp;
    }
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return 1;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    long long res = power(a, b);
    printf("%lld\n", res);
    return 0;
}