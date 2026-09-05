#include <stdio.h>
#include <math.h>
#include <limits.h>

unsigned long long next_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }

    unsigned long long unum = (unsigned long long)num;
    unsigned long long root = (unsigned long long)sqrt((double)unum);

    while (root * root <= unum) {
        if (root == ULONG_MAX / root) {
            break;
        }
        root++;
    }

    if (root > ULONG_MAX / root) {
        return 0;
    }

    return root * root;
}

int main(void) {
    long long test_values[] = { -10, 0, 1, 15, 16, 25, 26, 100, 999999999999 };
    size_t count = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < count; i++) {
        unsigned long long result = next_perfect_square(test_values[i]);
        printf("next_perfect_square(%lld) = %llu\n", test_values[i], result);
    }

    return 0;
}