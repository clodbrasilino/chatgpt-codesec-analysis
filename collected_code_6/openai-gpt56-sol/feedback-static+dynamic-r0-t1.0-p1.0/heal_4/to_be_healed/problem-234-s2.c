#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
    char *input = NULL;
    char *end;
    size_t capacity = 0;
    size_t length = 0;
    double side;
    double volume;
    int ch;
    int status = EXIT_FAILURE;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *replacement;
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > (size_t)-1 / 2) {
                    fputs("Input is too long.\n", stderr);
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            replacement = realloc(input, new_capacity);
            if (replacement == NULL) {
                fputs("Unable to allocate input buffer.\n", stderr);
                goto cleanup;
            }

            input = replacement;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read the side length.\n", stderr);
        goto cleanup;
    }

    if (ch == EOF && length == 0) {
        fputs("Failed to read the side length.\n", stderr);
        goto cleanup;
    }

    if (length + 1 >= capacity) {
        char *replacement;
        size_t new_capacity;

        if (length == (size_t)-1) {
            fputs("Input is too long.\n", stderr);
            goto cleanup;
        }

        new_capacity = length + 1;
        replacement = realloc(input, new_capacity);
        if (replacement == NULL) {
            fputs("Unable to allocate input buffer.\n", stderr);
            goto cleanup;
        }

        input = replacement;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = new_capacity;
    }

    input[length] = '\0';

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid side length.\n", stderr);
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || cube_volume(side, &volume) != 0) {
        fputs("Side length must be a finite, nonnegative value whose volume is representable.\n",
              stderr);
        goto cleanup;
    }

    if (printf("%.17g\n", volume) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}