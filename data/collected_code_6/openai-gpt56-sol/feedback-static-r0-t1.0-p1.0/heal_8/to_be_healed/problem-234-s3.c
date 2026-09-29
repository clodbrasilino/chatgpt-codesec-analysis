#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isspace'
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int cube_volume(double side, double *volume)
{
    double limit;
    double result;

    if (volume == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    limit = cbrt(DBL_MAX);
    if (side > limit) {
        return -1;
    }

    result = side * side * side;
    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

static int read_side(double *side)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char extra;
    char *end;

    if (side == NULL) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        if (fscanf(stdin, "%c", &extra) == 1) {
            while (extra != '\n') {
                if (fscanf(stdin, "%c", &extra) != 1) {
                    break;
                }
            }
        }
        return 1;
    }

    errno = 0;
    *side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        return 2;
    }

    /* Possible weaknesses found:
     *  include the header <ctype.h> or explicitly provide a declaration for 'isspace'
     *  call to undeclared library function 'isspace' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'isspace' [-Wimplicit-function-declaration]
     */
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 2;
    }

    return 0;
}

int main(void)
{
    double side;
    double volume;
    int status;

    status = read_side(&side);
    if (status < 0) {
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 1) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 2) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cube_volume(side, &volume) != 0) {
        fputs("The side length must be finite, nonnegative, and within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}