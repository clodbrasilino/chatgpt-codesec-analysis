#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isspace'
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int read_positive_double(const char *name, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *end;
    double parsed_value;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (name == NULL || value == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fprintf(stderr, "Failed to read the %s diagonal.\n", name);
        return 0;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     */
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fprintf(stderr, "Invalid %s diagonal.\n", name);
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed_value = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed_value) ||
        parsed_value <= 0.0) {
        fprintf(stderr, "Invalid %s diagonal.\n", name);
        return 0;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'isspace' [-Wimplicit-function-declaration]
     *  include the header <ctype.h> or explicitly provide a declaration for 'isspace'
     *  call to undeclared library function 'isspace' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid %s diagonal.\n", name);
        return 0;
    }

    *value = parsed_value;
    return 1;
}

static int rhombus_area(double diagonal1, double diagonal2, double *area)
{
    double half_diagonal;
    double result;

    if (area == NULL || !isfinite(diagonal1) || !isfinite(diagonal2) ||
        diagonal1 <= 0.0 || diagonal2 <= 0.0) {
        return 0;
    }

    half_diagonal = diagonal1 / 2.0;

    if (half_diagonal > DBL_MAX / diagonal2) {
        return 0;
    }

    result = half_diagonal * diagonal2;

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

int main(void)
{
    double diagonal1;
    double diagonal2;
    double area;

    if (!read_positive_double("first", &diagonal1) ||
        !read_positive_double("second", &diagonal2)) {
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