#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 5, got <no output>
  *  test case 1 failed: expected 8, got <no output>
  *  test case 2 failed: expected 7, got <no output>
  */

int count_digits(long long n) {
    if (n == 0) {
        return 1;
    }
    if (n == LLONG_MIN) {
        return 19;
    }
    if (n < 0) {
        n = -n;
    }
    int count = 0;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(argv[1]);
    if (len == 0 || len > 19) {
        if (strcmp(argv[1], "-9223372036854775808") != 0) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }
    char *endptr;
    long long num = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int digits = count_digits(num);
    printf("%d\n", digits);
    return EXIT_SUCCESS;
}