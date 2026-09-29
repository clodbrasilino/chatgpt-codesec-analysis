#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

int is_odd(int num) {
    return num & 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return EXIT_FAILURE;
    }

    if (val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input: integer out of range\n");
        return EXIT_FAILURE;
    }

    int num = (int)val;

    if (is_odd(num)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}