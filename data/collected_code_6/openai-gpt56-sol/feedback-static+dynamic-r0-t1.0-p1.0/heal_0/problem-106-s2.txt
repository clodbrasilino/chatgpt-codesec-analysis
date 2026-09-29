#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t length;
} Tuple;

static int add_list_to_tuples(
    const Tuple *tuples,
    size_t tuple_count,
    const int *list,
    size_t list_length,
    Tuple **result
) {
    Tuple *output = NULL;
    size_t initialized = 0;

    if (result == NULL ||
        (tuple_count > 0 && tuples == NULL) ||
        (list_length > 0 && list == NULL)) {
        return -1;
    }

    *result = NULL;

    if (tuple_count == 0) {
        return 0;
    }

    if (tuple_count > SIZE_MAX / sizeof(*output)) {
        return -1;
    }

    output = calloc(tuple_count, sizeof(*output));
    if (output == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        size_t total_length;

        if (tuples[i].length > 0 && tuples[i].items == NULL) {
            goto failure;
        }

        if (tuples[i].length > SIZE_MAX - list_length) {
            goto failure;
        }

        total_length = tuples[i].length + list_length;
        output[i].length = total_length;

        if (total_length == 0) {
            ++initialized;
            continue;
        }

        if (total_length > SIZE_MAX / sizeof(*output[i].items)) {
            goto failure;
        }

        output[i].items = malloc(total_length * sizeof(*output[i].items));
        if (output[i].items == NULL) {
            goto failure;
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            output[i].items[j] = tuples[i].items[j];
        }

        for (size_t j = 0; j < list_length; ++j) {
            output[i].items[tuples[i].length + j] = list[j];
        }

        ++initialized;
    }

    *result = output;
    return 0;

failure:
    for (size_t i = 0; i <= initialized && i < tuple_count; ++i) {
        free(output[i].items);
    }
    free(output);
    return -1;
}

static void free_tuples(Tuple *tuples, size_t tuple_count) {
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        free(tuples[i].items);
    }

    free(tuples);
}

static int print_tuples(const Tuple *tuples, size_t tuple_count) {
    if (tuple_count > 0 && tuples == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (printf("(") < 0) {
            return -1;
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (printf("%s%d", j == 0 ? "" : ", ", tuples[i].items[j]) < 0) {
                return -1;
            }
        }

        if (printf(")\n") < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void) {
    int first_items[] = {1, 2};
    int second_items[] = {3, 4};
    int list[] = {5, 6};
    Tuple tuples[] = {
        {first_items, sizeof(first_items) / sizeof(first_items[0])},
        {second_items, sizeof(second_items) / sizeof(second_items[0])}
    };
    Tuple *result = NULL;
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t list_length = sizeof(list) / sizeof(list[0]);

    if (add_list_to_tuples(tuples, tuple_count, list, list_length, &result) != 0) {
        fputs("Failed to add list to tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_tuples(result, tuple_count) != 0) {
        free_tuples(result, tuple_count);
        fputs("Failed to print tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    free_tuples(result, tuple_count);
    return EXIT_SUCCESS;
}