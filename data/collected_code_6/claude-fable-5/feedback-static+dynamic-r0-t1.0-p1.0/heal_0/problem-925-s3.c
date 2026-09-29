#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int tuple_product(const long *tuple, size_t count, long *result)
{
    size_t i;
    long product;

    if (tuple == NULL || result == NULL || count == 0U) {
        return -1;
    }

    product = 1L;

    for (i = 0U; i < count; i++) {
        if (product > 0L) {
            if (tuple[i] > 0L && product > LONG_MAX / tuple[i]) {
                return -2;
            }
            if (tuple[i] < 0L && tuple[i] < LONG_MIN / product) {
                return -2;
            }
        } else if (product < 0L) {
            if (tuple[i] > 0L && product < LONG_MIN / tuple[i]) {
                return -2;
            }
            if (tuple[i] < -1L && product < LONG_MAX / tuple[i]) {
                return -2;
            }
            if (tuple[i] == -1L && product == LONG_MIN) {
                return -2;
            }
        }
        product *= tuple[i];
    }

    *result = product;
    return 0;
}

int main(void)
{
    long tuple[] = {4L, 3L, 2L, 2L, -1L, 18L};
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    long result = 0L;
    int status;

    status = tuple_product(tuple, count, &result);

    if (status != 0) {
        if (fprintf(stderr, "Error computing product: %d\n", status) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Product: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}