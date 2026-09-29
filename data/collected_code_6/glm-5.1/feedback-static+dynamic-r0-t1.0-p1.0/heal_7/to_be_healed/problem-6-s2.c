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
    unsigned int xor_val = (unsigned int)(a ^ b);
    return xor_val != 0 && (xor_val & (xor_val - 1)) == 0;
}

int main(int argc, char * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1;
    char *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);

    if (endptr1 == argv[1] || *endptr1 != '\0' || val1 < INT_MIN || val1 > INT_MAX ||
        endptr2 == argv[2] || *endptr2 != '\0' || val2 < INT_MIN || val2 > INT_MAX) {
        return EXIT_FAILURE;
    }

    int a = (int)val1;
    int b = (int)val2;

    printf("%s\n", differ_at_one_bit(a, b) ? "True" : "False");

    return EXIT_SUCCESS;
}