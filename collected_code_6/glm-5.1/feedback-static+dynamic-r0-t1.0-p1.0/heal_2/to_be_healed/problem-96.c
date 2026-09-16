#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_divisors(int n) {
    if (n <= 0) {
        return 0;
    }

    int count = 0;
    for (int i = 1; i * i <= n; i++) {
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
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer format.\n");
        return EXIT_FAILURE;
    }

    if (val <= 0 || val > INT_MAX) {
        fprintf(stderr, "Error: Integer out of valid range (1 to %d).\n", INT_MAX);
        return EXIT_FAILURE;
    }

    int result = count_divisors((int)val);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}