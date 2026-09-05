#include <stdio.h>
#include <stdlib.h>

int count_divisors(long long n) {
    if (n <= 0) {
        return -1;
    }
    int count = 0;
    long long i;
    for (i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i == n) {
                count++;
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
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long long n = strtoll(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || n <= 0) {
        fprintf(stderr, "Error: Argument must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    int result = count_divisors(n);
    
    if (result < 0) {
        fprintf(stderr, "Error: Invalid input to count_divisors.\n");
        return EXIT_FAILURE;
    }
    
    printf("%d\n", result);
    return EXIT_SUCCESS;
}