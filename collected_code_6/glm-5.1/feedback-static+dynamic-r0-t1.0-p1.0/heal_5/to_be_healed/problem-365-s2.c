#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 5, got <no output>
  *  test case 1 failed: expected 8, got <no output>
  *  test case 2 failed: expected 7, got <no output>
  */

int count_digits(int number) {
    if (number == 0) {
        return 1;
    }
    int count = 0;
    unsigned int n;
    if (number == -2147483647 - 1) {
        n = (unsigned int)number;
    } else if (number < 0) {
        n = (unsigned int)(-number);
    } else {
        n = (unsigned int)number;
    }
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char const * const argv[const]) {
    int number;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val < -2147483647 - 1 || val > 2147483647) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }
    number = (int)val;
    printf("%d\n", count_digits(number));
    return EXIT_SUCCESS;
}