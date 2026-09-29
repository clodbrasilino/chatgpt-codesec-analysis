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
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    double side;
    double volume;
    int ch;
    int status = EXIT_FAILURE;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length == capacity) {
            if (capacity > (SIZE_MAX - 1) / 2) {
                fputs("Input is too long.\n", stderr);
                goto cleanup;
            }

            new_capacity = capacity == 0 ? 64 : capacity * 2;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                fputs("Unable to allocate memory.\n", stderr);
                goto cleanup;
            }

            input = resized;
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

    if (length == capacity) {
        char *resized;

        if (capacity == SIZE_MAX) {
            fputs("Input is too long.\n", stderr);
            goto cleanup;
        }

        resized = realloc(input, capacity + 1);
        if (resized == NULL) {
            fputs("Unable to allocate memory.\n", stderr);
            goto cleanup;
        }

        input = resized;
        capacity++;
    }

    input[length] = '\0';

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid side length.\n", stderr);
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
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