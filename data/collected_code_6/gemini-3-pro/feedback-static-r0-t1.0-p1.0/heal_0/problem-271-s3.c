#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_fifth_powers_even(unsigned int n) {
    unsigned long long sum = 0;
    unsigned int i;
    for (i = 1; i <= n; i++) {
        unsigned long long current_even = i * 2;
        unsigned long long power = current_even * current_even * current_even * current_even * current_even;
        sum += power;
    }
    return sum;
}

int main(void) {
    unsigned int n;
    int result;

    result = scanf("%u", &n);
    if (result != 1) {
        return EXIT_FAILURE;
    }

    if (n > 200) {
        return EXIT_FAILURE; 
    }

    unsigned long long sum = sum_of_fifth_powers_even(n);
    printf("%llu\n", sum);

    return EXIT_SUCCESS;
}