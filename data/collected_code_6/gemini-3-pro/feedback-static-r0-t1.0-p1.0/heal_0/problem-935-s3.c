#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_squares(unsigned int n) {
    unsigned long long num;
    
    if (n == 0) {
        return 0;
    }
    
    num = (unsigned long long)n;
    return (num * (num + 1) * (2 * num + 1)) / 6;
}

int main(void) {
    int input = 0;
    unsigned long long result = 0;

    if (scanf("%d", &input) != 1) {
        return EXIT_FAILURE;
    }

    if (input < 0) {
        return EXIT_FAILURE;
    }

    result = sum_of_squares((unsigned int)input);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}