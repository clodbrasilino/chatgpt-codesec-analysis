#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

bool differ_at_one_bit(int a, int b) {
    int xor_val = a ^ b;
    if (xor_val == 0) {
        return false;
    }
    if ((xor_val & (xor_val - 1)) == 0) {
        return true;
    }
    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1;
    char *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);

    if (val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX || *endptr1 != '\0' || *endptr2 != '\0') {
        return EXIT_FAILURE;
    }

    int a = (int)val1;
    int b = (int)val2;

    printf("%s\n", differ_at_one_bit(a, b) ? "True" : "False");

    return EXIT_SUCCESS;
}