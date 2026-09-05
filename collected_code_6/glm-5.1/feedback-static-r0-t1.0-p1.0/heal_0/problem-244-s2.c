#include <stdio.h>
#include <math.h>
#include <limits.h>

unsigned long long next_perfect_square(unsigned long long n) {
    unsigned long long root = (unsigned long long)sqrt((double)n);
    while (root * root <= n) {
        if (root == ULONG_MAX) {
            return 0;
        }
        root++;
    }
    return root * root;
}

int main(void) {
    unsigned long long num;
    if (scanf("%llu", &num) == 1) {
        unsigned long long result = next_perfect_square(num);
        if (result > num) {
            printf("%llu\n", result);
        } else {
            printf("Overflow\n");
        }
    }
    return 0;
}