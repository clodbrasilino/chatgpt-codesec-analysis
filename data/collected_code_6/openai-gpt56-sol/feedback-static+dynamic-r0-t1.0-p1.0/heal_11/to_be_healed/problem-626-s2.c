#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int largest_inscribed_triangle(double radius, double *area)
{
    if (area == NULL || !isfinite(radius) || radius <= 0.0 ||
        radius > sqrt(DBL_MAX)) {
        return -1;
    }

    *area = radius * radius;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    double radius;
    double area;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the radius.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || largest_inscribed_triangle(radius, &area) != 0) {
        fprintf(stderr, "Radius must be a positive finite number.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        fprintf(stderr, "Failed to write the result.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}