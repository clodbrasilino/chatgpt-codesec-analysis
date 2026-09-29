#include <stdio.h>
#include <stdlib.h>

unsigned int find_common_divisor(unsigned int a, unsigned int b) {
    if (a == 0 || b == 0) {
        return 0;
    }

    unsigned int min_val = a < b ? a : b;
    unsigned int max_divisor = 1;

    for (unsigned int i = 2; i <= min_val; ++i) {
        if (a % i == 0 && b % i == 0) {
            max_divisor = i;
        }
    }

    return max_divisor;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned int a = (unsigned int)strtoul(argv[1], NULL, 10);
    unsigned int b = (unsigned int)strtoul(argv[2], NULL, 10);

    unsigned int result = find_common_divisor(a, b);
    printf("%u\n", result);

    return EXIT_SUCCESS;
}