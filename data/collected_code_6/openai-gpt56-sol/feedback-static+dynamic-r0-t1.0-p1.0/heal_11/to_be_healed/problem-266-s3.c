#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

#define MAX_INPUT_LENGTH 4095U

static int cube_lateral_surface_area(double side, double *area)
{
    const double limit = sqrt(DBL_MAX / 4.0);

    if (area == NULL || !isfinite(side) || side < 0.0 || side > limit) {
        return -1;
    }

    *area = 4.0 * side * side;
    return 0;
}

static int discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    for (;;) {
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            return ferror(stdin) ? -1 : 0;
        }

        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'strchr'
         *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        if (strchr(buffer, '\n') != NULL) {
            return 0;
        }
    }
}

static int read_line(char **line)
{
    char *buffer;
    size_t length = 0;
    size_t remaining;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(MAX_INPUT_LENGTH + 2U);
    if (buffer == NULL) {
        return -1;
    }

    remaining = MAX_INPUT_LENGTH + 2U;

    while (remaining > 1U) {
        /* Possible weaknesses found:
         *  Variable 'result' can be declared as pointer to const [constVariablePointer]
         */
        char *result = fgets(buffer + length, (int)remaining, stdin);
        char *newline;
        size_t chunk_length;

        if (result == NULL) {
            if (ferror(stdin) || length == 0U) {
                free(buffer);
                return -1;
            }
            break;
        }

        newline = strchr(buffer + length, '\n');
        /* Possible weaknesses found:
         *  include '<string.h>' or provide a declaration of 'strlen'
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         */
        chunk_length = strlen(buffer + length);

        if (newline != NULL) {
            *newline = '\0';
            *line = buffer;
            return 0;
        }

        length += chunk_length;
        remaining -= chunk_length;

        if (feof(stdin)) {
            break;
        }

        if (chunk_length == 0U) {
            free(buffer);
            return -1;
        }
    }

    if (length > MAX_INPUT_LENGTH) {
        int status = discard_line();
        free(buffer);
        return status == 0 ? -1 : status;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *end;
    double side;
    double area;

    if (read_line(&input) != 0) {
        fputs("Failed to read the cube side length.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(side)) {
        free(input);
        fputs("Invalid cube side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || cube_lateral_surface_area(side, &area) != 0) {
        free(input);
        fputs("Invalid cube side length.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}