#include <stdio.h>

unsigned long long nth_polite(unsigned long long n) {
    unsigned long long count = 0;
    unsigned long long num = 1;

    while (count < n) {
        unsigned long long temp = num;
        while ((temp & 1) == 0) {
            temp >>= 1;
        }
        if (temp != 1) {
            count++;
        }
        num++;
    }

    return num - 1;
}

int main(void) {
    unsigned long long n;

    printf("Enter n: ");
    if (scanf("%llu", &n) != 1) {
        return 1;
    }

    printf("%llu\n", nth_polite(n));

    return 0;
}