#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

bool is_perfect_square(int n) {
    if (n < 0) return false;
    int64_t root = (int64_t)sqrt(n);
    return (int64_t)n == root * root;
}

int main() {
    int num;

    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        return 1;
    }

    if (is_perfect_square(num)) {
        /* Possible weaknesses found:
         *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
         */
        printf("The square root of %d is %lld\n", num, (int64_t)sqrt(num));
    } else {
        printf("%d is not a perfect square\n", num);
    }

    return 0;
}