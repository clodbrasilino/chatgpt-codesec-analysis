#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_elements(const intmax_t *input, intmax_t *output, size_t count)
{
    if (count != 0 && (input == NULL || output == NULL)) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        const intmax_t value = input[i];

        if (value != 0) {
            if (value > 0) {
                if (value > INTMAX_MAX / value) {
                    return -1;
                }
            /* Possible weaknesses found:
             * UBSan: division of -9223372036854775808 by -1 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:28424,execs:5316,op:havoc,rep:3)
             */
            } else if (value < INTMAX_MIN / value) {
                return -1;
            }
        }

        const intmax_t square = value * value;

        if (value > 0) {
            if (square > INTMAX_MAX / value) {
                return -1;
            }
        } else if (value < 0) {
            if (square > INTMAX_MIN / value) {
                return -1;
            }
        }

        output[i] = square * value;
    }

    return 0;
}

int main(void)
{
    size_t count = 0;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(intmax_t)) {
        fputs("Element count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    intmax_t *values = NULL;
    intmax_t *cubes = NULL;

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        cubes = malloc(count * sizeof(*cubes));

        if (values == NULL || cubes == NULL) {
            fputs("Memory allocation failed\n", stderr);
            free(cubes);
            free(values);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNdMAX, &values[i]) != 1) {
            fputs("Invalid element\n", stderr);
            free(cubes);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (cube_elements(values, cubes, count) != 0) {
        fputs("Cube calculation overflow\n", stderr);
        free(cubes);
        free(values);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        const char separator = i + 1 == count ? '\n' : ' ';

        if (printf("%" PRIdMAX "%c", cubes[i], separator) < 0) {
            free(cubes);
            free(values);
            return EXIT_FAILURE;
        }
    }

    free(cubes);
    free(values);
    return EXIT_SUCCESS;
}