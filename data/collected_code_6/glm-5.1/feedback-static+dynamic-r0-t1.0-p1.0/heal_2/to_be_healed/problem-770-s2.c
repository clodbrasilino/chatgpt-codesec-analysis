#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_fourth_power_odd(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    int count = 0;
    unsigned long long i = 1;
    
    while (count < n) {
        sum += i * i * i * i;
        i += 2;
        count++;
    }
    
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int n;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        return EXIT_FAILURE;
    }
    
    unsigned long long result = sum_fourth_power_odd(n);
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}