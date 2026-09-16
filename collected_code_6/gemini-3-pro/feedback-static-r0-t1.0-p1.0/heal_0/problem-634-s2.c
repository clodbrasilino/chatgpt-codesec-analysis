#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_fourth_powers_of_even_numbers(int n) {
    if (n < 0) {
        return 0;
    }

    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long even_num = 2ULL * i;
        sum += even_num * even_num * even_num * even_num;
    }
    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 0) {
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_of_fourth_powers_of_even_numbers(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}