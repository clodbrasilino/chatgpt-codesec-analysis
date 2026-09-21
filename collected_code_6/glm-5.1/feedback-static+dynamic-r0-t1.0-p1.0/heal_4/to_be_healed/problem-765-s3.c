#include <stdio.h>
#include <stdlib.h>

unsigned long long nth_polite_number(unsigned long long n) {
    unsigned long long position = 1;
    unsigned long long m = 1;
    unsigned long long result = 1;
    while (position < n) {
        m++;
        if ((m & (m - 1)) != 0) {
            position++;
            result = m;
        }
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    char *endptr;
    unsigned long long n = strtoull(argv[1], &endptr, 10);
    if (*endptr != '\0' || n == 0) {
        fprintf(stderr, "Invalid input: n must be a positive integer\n");
        return 1;
    }
    unsigned long long res = nth_polite_number(n);
    printf("%llu\n", res);
    return 0;
}