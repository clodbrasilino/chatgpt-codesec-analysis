#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_divisors(int n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned int un;
    if (n < 0) {
        un = (unsigned int)(-(n + 1)) + 1u;
    } else {
        un = (unsigned int)n;
    }
    
    int count = 0;
    unsigned int i;
    for (i = 1; i * i <= un; i++) {
        if (un % i == 0) {
            if (i * i == un) {
                count += 1;
            } else {
                count += 2;
            }
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: Invalid integer format\n");
        return EXIT_FAILURE;
    }
    
    if (val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Error: Integer overflow\n");
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    printf("Number of divisors: %d\n", count_divisors(n));
    
    return EXIT_SUCCESS;
}