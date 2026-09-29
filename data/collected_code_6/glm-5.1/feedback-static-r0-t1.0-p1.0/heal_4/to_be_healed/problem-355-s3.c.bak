#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long count_rectangles(int r) {
    if (r < 0) {
        return 0;
    }

    long long count = 0;
    long long r_sq = (long long)r * r;
    
    for (long long x = 1; x <= r; x++) {
        for (long long y = 1; y <= r; y++) {
            if (x * x + y * y <= r_sq) {
                count++;
            }
        }
    }

    return count * 4;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val < 0 || val > 10000) {
        return EXIT_FAILURE;
    }

    long long result = count_rectangles((int)val);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}