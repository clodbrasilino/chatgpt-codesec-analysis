#include <stdio.h>
#include <stdlib.h>

unsigned long long lucas_number(unsigned int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    unsigned long long a = 2, b = 1, c;
    for (unsigned int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    unsigned int n;
    printf("Enter the value of n: ");
    if (scanf("%u", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    unsigned long long result = lucas_number(n);
    printf("The %u-th Lucas number is: %llu\n", n, result);
    return 0;
}