#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int cube_volume(double side, double *volume)
{
    double result;

    if (volume == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    result = side * side * side;

    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    double side;
    double volume;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the side length.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid side length.\n");
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || cube_volume(side, &volume) != 0) {
        fprintf(stderr,
                "Side length must be a finite, nonnegative value whose volume is representable.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", volume) < 0) {
        fprintf(stderr, "Failed to write the volume.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}