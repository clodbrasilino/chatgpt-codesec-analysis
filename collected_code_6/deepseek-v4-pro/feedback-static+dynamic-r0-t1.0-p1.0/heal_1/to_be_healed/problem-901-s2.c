#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
}

long long smallest_multiple(int n) {
    if (n <= 0) {
        return 0;
    }
    
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result = lcm(result, i);
    }
    
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long n = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || n <= 0 || n > 100) {
        fprintf(stderr, "Error: n must be a positive integer between 1 and 100\n");
        return EXIT_FAILURE;
    }
    
    long long result = smallest_multiple((int)n);
    printf("The smallest multiple of the first %ld numbers is: %lld\n", n, result);
    
    return EXIT_SUCCESS;
}