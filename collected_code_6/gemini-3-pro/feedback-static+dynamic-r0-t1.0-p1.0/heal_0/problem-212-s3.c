#include <stdio.h>
#include <stdlib.h>

unsigned long long int sum_of_fourth_powers(unsigned int n) {
    unsigned long long int sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        unsigned long long int i_copy = (unsigned long long int)i;
        sum += i_copy * i_copy * i_copy * i_copy;
    }
    return sum;
}

int main(void) {
    unsigned int n;
    int result;

    result = scanf("%u", &n);
    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    unsigned long long int total_sum = sum_of_fourth_powers(n);
    printf("%llu\n", total_sum);

    return 0;
}