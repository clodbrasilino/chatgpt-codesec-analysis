#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <float.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 25, got <no output>
  *  test case 2 failed: expected 4, got <no output>
  *  test case 0 failed: expected 100, got <no output>
  */

double rhombus_area(double diagonal1, double diagonal2) {
    if (diagonal1 <= 0 || diagonal2 <= 0) {
        return -1.0;
    }
    if (diagonal1 > DBL_MAX / diagonal2) {
        return -1.0;
    }
    return (diagonal1 * diagonal2) / 2.0;
}

int read_double(double *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *endptr;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 0;
    }

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    } else {
        if (len == sizeof(input) - 1) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
                if (ch < 0) {
                    break;
                }
            }
        }
        fprintf(stderr, "Input too long\n");
        return 0;
    }

    errno = 0;
    *value = strtod(input, &endptr);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }
    if (endptr == input) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }
    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return 0;
    }

    return 1;
}

int main(void) {
    double d1, d2, area;

    printf("Enter length of first diagonal: ");
    if (!read_double(&d1)) {
        return EXIT_FAILURE;
    }

    printf("Enter length of second diagonal: ");
    if (!read_double(&d2)) {
        return EXIT_FAILURE;
    }

    area = rhombus_area(d1, d2);
    if (area < 0) {
        fprintf(stderr, "Diagonals must be positive and result must be representable\n");
        return EXIT_FAILURE;
    }

    printf("Area of rhombus: %.2f\n", area);
    return EXIT_SUCCESS;
}