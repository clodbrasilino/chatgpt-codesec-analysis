#include <stdio.h>
#include <stdlib.h>

int find_smallest_prime_divisor(long long n) {
    if (n < 2) {
        return -1;
    }
    if (n % 2 == 0) {
        return 2;
    }
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return (int)i;
        }
    }
    return (int)n;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    long long num;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }
    char *endptr;
    num = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0' || num < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    int result = find_smallest_prime_divisor(num);
    if (result == -1) {
        printf("No prime divisor found.\n");
    } else {
        printf("%d\n", result);
    }
    return 0;
}