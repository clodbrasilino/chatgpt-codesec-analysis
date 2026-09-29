#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

static void *allocate_array(size_t count, size_t element_size)
{
    if (count == 0) {
        return NULL;
    }

    if (element_size == 0 || count > SIZE_MAX / element_size) {
        return NULL;
    }

    return malloc(count * element_size);
}

static bool rearrange_tuples(const Tuple *tuples, size_t tuple_count,
                             const int *order, size_t order_count,
                             Tuple *result)
{
    unsigned char *used;
    size_t i;
    size_t j;

    if (tuple_count != order_count) {
        return false;
    }

    if (tuple_count == 0) {
        return true;
    }

    if (tuples == NULL || order == NULL || result == NULL) {
        return false;
    }

    used = calloc(tuple_count, sizeof(*used));
    if (used == NULL) {
        return false;
    }

    for (i = 0; i < order_count; ++i) {
        bool found = false;

        for (j = 0; j < tuple_count; ++j) {
            if (used[j] == 0 && tuples[j].key == order[i]) {
                result[i] = tuples[j];
                used[j] = 1;
                found = true;
                break;
            }
        }

        if (!found) {
            free(used);
            return false;
        }
    }

    free(used);
    return true;
}

int main(void)
{
    size_t count;
    size_t i;
    Tuple *tuples = NULL;
    Tuple *result = NULL;
    int *order = NULL;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    if (count > 0) {
        tuples = allocate_array(count, sizeof(*tuples));
        order = allocate_array(count, sizeof(*order));
        result = allocate_array(count, sizeof(*result));

        if (tuples == NULL || order == NULL || result == NULL) {
            goto cleanup;
        }
    }

    for (i = 0; i < count; ++i) {
        if (scanf("%d %d", &tuples[i].key, &tuples[i].value) != 2) {
            goto cleanup;
        }
    }

    for (i = 0; i < count; ++i) {
        if (scanf("%d", &order[i]) != 1) {
            goto cleanup;
        }
    }

    if (!rearrange_tuples(tuples, count, order, count, result)) {
        goto cleanup;
    }

    for (i = 0; i < count; ++i) {
        if (printf("%d %d\n", result[i].key, result[i].value) < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    free(order);
    free(tuples);
    return status;
}