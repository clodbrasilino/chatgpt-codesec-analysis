#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int nth_ap_term(int a, int d, int n) {
    if (n <= 0) {
        return -1;
    }
    return a + (n - 1) * d;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_diff> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_a, *endptr_d, *endptr_n;
    long val_a, val_d, val_n;

    val_a = strtol(argv[1], &endptr_a, 10);
    if (*endptr_a != '\0' || endptr_a == argv[1]) {
        fprintf(stderr, "Invalid first term\n");
        return EXIT_FAILURE;
    }

    val_d = strtol(argv[2], &endptr_d, 10);
    if (*endptr_d != '\0' || endptr_d == argv[2]) {
        fprintf(stderr, "Invalid common difference\n");
        return EXIT_FAILURE;
    }

    val_n = strtol(argv[3], &endptr_n, 10);
    if (*endptr_n != '\0' || endptr_n == argv[3] || val_n <= 0) {
        fprintf(stderr, "Invalid n. n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MAX' undeclared (first use in this function)
     */
    if (val_a < INT_MIN || val_a > INT_MAX || val_d < INT_MIN || val_d > INT_MAX) {
        fprintf(stderr, "Arithmetic overflow on input\n");
        return EXIT_FAILURE;
    }

    int a = (int)val_a;
    int d = (int)val_d;
    int n = (int)val_n;

    long long result = (long long)a + (long long)(n - 1) * d;

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  use of undeclared identifier 'INT_MIN'
     */
    if (result < INT_MIN || result > INT_MAX) {
        fprintf(stderr, "Arithmetic overflow on result calculation\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", (int)result);

    return EXIT_SUCCESS;
}