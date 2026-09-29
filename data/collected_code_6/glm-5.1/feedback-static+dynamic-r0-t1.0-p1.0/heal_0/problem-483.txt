#include <stdio.h>

unsigned long long find_first_factorial_divisible_by_x(unsigned long long x) {
    if (x == 0) {
        return 0;
    }
    unsigned long long n = 1;
    unsigned long long factorial = 1;
    while (factorial % x != 0) {
        n++;
        factorial *= n;
    }
    return n;
}

int main(void) {
    unsigned long long x;
    if (scanf("%llu", &x) == 1) {
        unsigned long long result = find_first_factorial_divisible_by_x(x);
        printf("%llu\n", result);
        return 0;
    }
    return 1;
}