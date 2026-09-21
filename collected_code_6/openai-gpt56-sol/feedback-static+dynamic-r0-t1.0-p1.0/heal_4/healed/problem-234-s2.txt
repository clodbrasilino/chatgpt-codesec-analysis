#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdint.h>
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
    char *end = NULL;
    size_t capacity = 0;
    size_t length = 0;
    double side;
    double volume;
    int ch;
    int status = EXIT_FAILURE;

    for (;;) {
        char *replacement;
        size_t new_capacity;

        ch = fgetc(stdin);
        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            fputs("Input is too long.\n", stderr);
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
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

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Unable to allocate input buffer.\n", stderr);
            goto cleanup;
        }
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