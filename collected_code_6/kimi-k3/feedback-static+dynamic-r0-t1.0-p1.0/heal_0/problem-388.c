#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int highest_power_of_2(unsigned int n, unsigned int *result) {
    if (result == NULL) {
        return -1;
    }
    if (n == 0) {
        return -1;
    }
    
    unsigned int power = 1;
    while (power <= n / 2) {
        power *= 2;
    }
    *result = power;
    return 0;
}

int main(void) {
    unsigned int n;
    unsigned int result;
    
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (highest_power_of_2(n, &result) != 0) {
        fprintf(stderr, "Error: n must be greater than 0\n");
        return 1;
    }
    
    printf("%u\n", result);
    return 0;
}