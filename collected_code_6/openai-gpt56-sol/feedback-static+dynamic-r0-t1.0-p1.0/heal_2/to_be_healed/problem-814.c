#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int read_positive_double(const char *message, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs(message, stderr);
        return 0;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Input is too long.\n", stderr);
        return 0;
    }

    errno = 0;
    end = NULL;
    *value = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(*value) || *value <= 0.0) {
        fputs("Invalid diagonal.\n", stderr);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid diagonal.\n", stderr);
        return 0;
    }

    return 1;
}

static int rhombus_area(double diagonal1, double diagonal2, double *area)
{
    if (area == NULL || !isfinite(diagonal1) || !isfinite(diagonal2) ||
        diagonal1 <= 0.0 || diagonal2 <= 0.0) {
        return 0;
    }

    *area = (diagonal1 / 2.0) * diagonal2;
    return isfinite(*area);
}

int main(void)
{
    double diagonal1;
    double diagonal2;
    double area;

    if (!read_positive_double("Failed to read the first diagonal.\n",
                              &diagonal1)) {
        return EXIT_FAILURE;
    }

    if (!read_positive_double("Failed to read the second diagonal.\n",
                              &diagonal2)) {
        return EXIT_FAILURE;
    }

    if (!rhombus_area(diagonal1, diagonal2, &area)) {
        fputs("Unable to calculate a finite area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}