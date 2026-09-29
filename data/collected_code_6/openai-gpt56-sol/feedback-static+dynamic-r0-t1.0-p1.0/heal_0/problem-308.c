#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t product;
    size_t left_index;
    size_t right_index;
} Product;

static int compare_products_desc(const void *lhs, const void *rhs)
{
    const Product *a = lhs;
    const Product *b = rhs;

    if (a->product < b->product) {
        return 1;
    }
    if (a->product > b->product) {
        return -1;
    }
    if (a->left_index > b->left_index) {
        return 1;
    }
    if (a->left_index < b->left_index) {
        return -1;
    }
    if (a->right_index > b->right_index) {
        return 1;
    }
    if (a->right_index < b->right_index) {
        return -1;
    }
    return 0;
}

static int find_largest_products(const int32_t *left, size_t left_count,
                                 const int32_t *right, size_t right_count,
                                 size_t requested_count, Product **results,
                                 size_t *result_count)
{
    Product *products = NULL;
    size_t product_count;
    size_t output_count;
    size_t index = 0;

    if (results == NULL || result_count == NULL) {
        return EINVAL;
    }

    *results = NULL;
    *result_count = 0;

    if (requested_count == 0) {
        return 0;
    }

    if (left == NULL || right == NULL || left_count == 0 || right_count == 0) {
        return EINVAL;
    }

    if (left_count > SIZE_MAX / right_count) {
        return EOVERFLOW;
    }

    product_count = left_count * right_count;

    if (product_count > SIZE_MAX / sizeof(*products)) {
        return EOVERFLOW;
    }

    products = malloc(product_count * sizeof(*products));
    if (products == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0; i < left_count; ++i) {
        for (size_t j = 0; j < right_count; ++j) {
            products[index].product = (int64_t)left[i] * (int64_t)right[j];
            products[index].left_index = i;
            products[index].right_index = j;
            ++index;
        }
    }

    qsort(products, product_count, sizeof(*products), compare_products_desc);

    output_count = requested_count < product_count
                       ? requested_count
                       : product_count;

    if (output_count < product_count) {
        Product *resized = realloc(products, output_count * sizeof(*products));
        if (resized != NULL) {
            products = resized;
        }
    }

    *results = products;
    *result_count = output_count;
    return 0;
}

int main(void)
{
    const int32_t left[] = {3, -4, 7, 2};
    const int32_t right[] = {5, -6, 8};
    const size_t requested_count = 5;
    Product *results = NULL;
    size_t result_count = 0;
    int status;

    status = find_largest_products(
        left, sizeof(left) / sizeof(left[0]),
        right, sizeof(right) / sizeof(right[0]),
        requested_count, &results, &result_count
    );

    if (status != 0) {
        fprintf(stderr, "find_largest_products failed: %d\n", status);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; ++i) {
        printf("%" PRId64 "\n", results[i].product);
    }

    free(results);
    return EXIT_SUCCESS;
}