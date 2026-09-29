#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_keith_number(long n) {
    long t = n;
    int digits[100], j, k, sum = 0, i = 0;
    for (; t > 0; ++i) {
        digits[i] = t % 10;
        t /= 10;
    }
    k = i;
    while (sum <= n) {
        sum = 0;
        for (j = 0; j < k; ++j)
            sum += digits[j];
        if (sum == n) return true;
        for (j = 0; j < k - 1; ++j)
            digits[j] = digits[j + 1];
        digits[k - 1] = sum;
    }
    return false;
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_keith_number(number)) {
        printf("%ld is a Keith number.\n", number);
    } else {
        printf("%ld is not a Keith number.\n", number);
    }

    return EXIT_SUCCESS;
}