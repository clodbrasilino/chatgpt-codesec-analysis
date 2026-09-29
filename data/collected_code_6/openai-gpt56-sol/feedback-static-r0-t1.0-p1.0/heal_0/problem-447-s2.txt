#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int cube_int64(int64_t value, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if (value > 2097151 || value < -2097152) {
        return -1;
    }

    *result = value * value * value;
    return 0;
}

int main(void)
{
    size_t count;

    if (printf("Enter the number of elements: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(int64_t)) {
        fprintf(stderr, "Invalid element count.\n");
        return EXIT_FAILURE;
    }

    int64_t *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("Element %zu: ", i + 1) < 0 ||
            scanf("%" SCNd64, &values[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t cube;

        if (cube_int64(values[i], &cube) != 0) {
            fprintf(stderr, "Cube of element %zu is outside the int64_t range.\n",
                    i + 1);
            free(values);
            return EXIT_FAILURE;
        }

        if (printf("%" PRId64 "%c", cube, i + 1 == count ? '\n' : ' ') < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    free(values);
    return EXIT_SUCCESS;
}