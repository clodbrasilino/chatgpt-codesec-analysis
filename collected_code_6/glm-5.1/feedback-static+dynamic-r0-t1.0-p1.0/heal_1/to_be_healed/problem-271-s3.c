#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long sum_fifth_power_even(int n) {
    unsigned long long sum = 0;
    
    if (n <= 0) {
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        unsigned long long even_num = 2ULL * i;
        unsigned long long max_root = ULLONG_MAX / even_num;
        
        if (even_num > max_root) {
            fprintf(stderr, "Overflow detected\n");
            exit(EXIT_FAILURE);
        }
        
        unsigned long long squared = even_num * even_num;
        unsigned long long fourth_power = squared * squared;
        
        if (fourth_power > ULLONG_MAX / even_num) {
            fprintf(stderr, "Overflow detected\n");
            exit(EXIT_FAILURE);
        }
        
        unsigned long long fifth_power = fourth_power * even_num;
        
        if (sum > ULLONG_MAX - fifth_power) {
            fprintf(stderr, "Overflow detected\n");
            exit(EXIT_FAILURE);
        }
        
        sum += fifth_power;
    }
    
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    long val = strtol(argv[1], NULL, 10);
    
    if (val <= 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input: n must be a positive integer within int range\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    unsigned long long result = sum_fifth_power_even(n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}