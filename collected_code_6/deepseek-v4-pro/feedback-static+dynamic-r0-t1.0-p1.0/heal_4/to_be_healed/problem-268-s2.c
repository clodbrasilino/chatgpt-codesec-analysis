#include <stdio.h>
#include <stdlib.h>

long long star_number(int n) {
    if (n <= 0) {
        return -1;
    }
    if (n > 46340) {
        return -1;
    }
    return 6LL * n * (n - 1) + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long n = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || endptr == argv[1] || n <= 0 || n > 46340) {
        fprintf(stderr, "Error: Invalid input. Please provide a positive integer less than or equal to 46340.\n");
        return EXIT_FAILURE;
    }
    
    long long result = star_number((int)n);
    printf("Star number %ld is %lld\n", n, result);
    
    return EXIT_SUCCESS;
}