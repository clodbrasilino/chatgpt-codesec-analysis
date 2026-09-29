#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const int *values;
    size_t size;
} TupleView;

typedef struct {
    int *values;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

void destroy_tuple_list(TupleList *list)
{
    if (list == NULL) {
        return;
    }

    if (list->tuples != NULL) {
        for (size_t i = 0; i < list->count; ++i) {
            free(list->tuples[i].values);
        }
    }

    free(list->tuples);
    free(list);
}

TupleList *trim_tuple_list(const TupleView *tuples, size_t count, size_t k)
{
    if (count > 0 && tuples == NULL) {
        return NULL;
    }

    TupleList *result = calloc(1, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    if (count == 0) {
        return result;
    }

    if (count > SIZE_MAX / sizeof(*result->tuples)) {
        destroy_tuple_list(result);
        return NULL;
    }

    result->tuples = calloc(count, sizeof(*result->tuples));
    if (result->tuples == NULL) {
        destroy_tuple_list(result);
        return NULL;
    }

    result->count = count;

    for (size_t i = 0; i < count; ++i) {
        if (tuples[i].size > 0 && tuples[i].values == NULL) {
            destroy_tuple_list(result);
            return NULL;
        }

        if (k >= tuples[i].size || tuples[i].size - k <= k) {
            continue;
        }

        size_t trimmed_size = tuples[i].size - k - k;

        if (trimmed_size > SIZE_MAX / sizeof(*result->tuples[i].values)) {
            destroy_tuple_list(result);
            return NULL;
        }

        result->tuples[i].values =
            malloc(trimmed_size * sizeof(*result->tuples[i].values));

        if (result->tuples[i].values == NULL) {
            destroy_tuple_list(result);
            return NULL;
        }

        memcpy(result->tuples[i].values,
               tuples[i].values + k,
               trimmed_size * sizeof(*result->tuples[i].values));

        result->tuples[i].size = trimmed_size;
    }

    return result;
}

bool print_tuple_list(const TupleList *list)
{
    if (list == NULL || (list->count > 0 && list->tuples == NULL)) {
        return false;
    }

    if (fputc('[', stdout) == EOF) {
        return false;
    }

    for (size_t i = 0; i < list->count; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (fputc('(', stdout) == EOF) {
            return false;
        }

        for (size_t j = 0; j < list->tuples[i].size; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
                return false;
            }

            if (printf("%d", list->tuples[i].values[j]) < 0) {
                return false;
            }
        }

        if (list->tuples[i].size == 1 && fputc(',', stdout) == EOF) {
            return false;
        }

        if (fputc(')', stdout) == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int first[] = {5, 3, 1, 9, 6};
    const int second[] = {3, 1, 7, 5, 10};
    const int third[] = {8, 2, 7, 3, 2};

    const TupleView tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    const size_t k = 2;
    TupleList *trimmed = trim_tuple_list(
        tuples,
        sizeof(tuples) / sizeof(tuples[0]),
        k
    );

    if (trimmed == NULL) {
        fputs("Unable to trim tuple list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_tuple_list(trimmed)) {
        destroy_tuple_list(trimmed);
        return EXIT_FAILURE;
    }

    destroy_tuple_list(trimmed);
    return EXIT_SUCCESS;
}