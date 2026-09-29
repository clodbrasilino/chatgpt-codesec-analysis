#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_int64_desc(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a < b) - (a > b);
}

static int largest_products(const int32_t *first, size_t first_count,
                            const int32_t *second, size_t second_count,
                            size_t requested, int64_t **result,
                            size_t *result_count)
{
    int64_t *products;
    size_t product_count;
    size_t index = 0;

    if (result == NULL || result_count == NULL) {
        return EINVAL;
    }

    *result = NULL;
    *result_count = 0;

    if ((first_count != 0 && first == NULL) ||
        (second_count != 0 && second == NULL)) {
        return EINVAL;
    }

    if (requested == 0 || first_count == 0 || second_count == 0) {
        return 0;
    }

    if (first_count > SIZE_MAX / second_count) {
        return EOVERFLOW;
    }

    product_count = first_count * second_count;

    if (product_count > SIZE_MAX / sizeof(*products)) {
        return EOVERFLOW;
    }

    products = malloc(product_count * sizeof(*products));
    if (products == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0; i < first_count; ++i) {
        for (size_t j = 0; j < second_count; ++j) {
            products[index++] = (int64_t)first[i] * (int64_t)second[j];
        }
    }

    qsort(products, product_count, sizeof(*products), compare_int64_desc);

    if (requested < product_count) {
        product_count = requested;
    }

    *result = products;
    *result_count = product_count;
    return 0;
}

int main(void)
{
    const int32_t first[] = {3, -2, 5, 1};
    const int32_t second[] = {4, -6, 2};
    const size_t requested = 5;
    int64_t *products = NULL;
    size_t product_count = 0;
    int status;

    status = largest_products(
        first,
        sizeof(first) / sizeof(first[0]),
        second,
        sizeof(second) / sizeof(second[0]),
        requested,
        &products,
        &product_count
    );

    if (status != 0) {
        fprintf(stderr, "largest_products failed with error %d\n", status);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < product_count; ++i) {
        printf("%" PRId64 "%c", products[i],
               i + 1 == product_count ? '\n' : ' ');
    }

    free(products);
    return EXIT_SUCCESS;
}