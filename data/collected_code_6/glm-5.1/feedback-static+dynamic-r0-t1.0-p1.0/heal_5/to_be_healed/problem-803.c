#include <stdio.h>
#include <stdlib.h>

int is_perfect_square(int num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long low = 1;
    long high = num;
    while (low <= high) {
        long mid = low + (high - low) / 2;
        long square = mid * mid;
        if (square == num) {
            return 1;
        } else if (square < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 2147483647) {
        fprintf(stderr, "Invalid input: must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    int num = (int)val;
    printf("%s\n", is_perfect_square(num) ? "True" : "False");
    return EXIT_SUCCESS;
}