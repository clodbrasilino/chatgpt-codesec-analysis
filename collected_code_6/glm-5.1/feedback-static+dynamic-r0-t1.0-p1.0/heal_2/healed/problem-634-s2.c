#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_fourth_power_even(int n) {
    if (n <= 0) {
        return 0;
    }

    unsigned long long sum = 0;
    unsigned long long even_num = 2;

    for (int i = 0; i < n; i++) {
        unsigned long long squared = even_num * even_num;
        sum += squared * squared;
        even_num += 2;
    }

    return sum;
}

int main(int argc, char * const argv[]) {
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }

    unsigned long long result = sum_fourth_power_even(n);
    printf("%llu\n", result);

    return 0;
}