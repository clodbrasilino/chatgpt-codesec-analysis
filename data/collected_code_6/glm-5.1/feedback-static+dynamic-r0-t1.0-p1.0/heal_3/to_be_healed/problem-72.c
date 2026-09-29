#include <stdio.h>
#include <stdlib.h>

int can_be_diff_of_squares(long long n) {
    if (n < 0) {
        n = -n;
    }
    if (n == 0) {
        return 1;
    }
    if (n % 4 == 2) {
        return 0;
    }
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    long long num;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%lld", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (can_be_diff_of_squares(num)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return EXIT_SUCCESS;
}