#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *const *values;
    size_t length;
} Tuple;

static int remove_all_none_tuples(Tuple *tuples, size_t *count)
{
    size_t original_count;
    size_t read_index;
    size_t write_index = 0;

    if (count == NULL) {
        return -1;
    }

    original_count = *count;

    if (original_count > 0 && tuples == NULL) {
        return -1;
    }

    for (read_index = 0; read_index < original_count; ++read_index) {
        if (tuples[read_index].length > 0 && tuples[read_index].values == NULL) {
            return -1;
        }
    }

    for (read_index = 0; read_index < original_count; ++read_index) {
        bool all_none = true;
        size_t value_index;

        for (value_index = 0;
             value_index < tuples[read_index].length;
             ++value_index) {
            if (tuples[read_index].values[value_index] != NULL) {
                all_none = false;
                break;
            }
        }

        if (!all_none) {
            if (write_index != read_index) {
                tuples[write_index] = tuples[read_index];
            }
            ++write_index;
        }
    }

    for (read_index = write_index; read_index < original_count; ++read_index) {
        tuples[read_index].values = NULL;
        tuples[read_index].length = 0;
    }

    *count = write_index;
    return 0;
}

static int print_tuple_list(const Tuple *tuples, size_t count)
{
    size_t tuple_index;

    if (count > 0 && tuples == NULL) {
        return -1;
    }

    if (putchar('[') == EOF) {
        return -1;
    }

    for (tuple_index = 0; tuple_index < count; ++tuple_index) {
        size_t value_index;

        if (tuples[tuple_index].length > 0 &&
            tuples[tuple_index].values == NULL) {
            return -1;
        }

        if (tuple_index > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('(') == EOF) {
            return -1;
        }

        for (value_index = 0;
             value_index < tuples[tuple_index].length;
             ++value_index) {
            const char *value = tuples[tuple_index].values[value_index];

            if (value_index > 0 && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (value == NULL) {
                if (fputs("None", stdout) == EOF) {
                    return -1;
                }
            } else {
                if (putchar('"') == EOF ||
                    fputs(value, stdout) == EOF ||
                    putchar('"') == EOF) {
                    return -1;
                }
            }
        }

        if (putchar(')') == EOF) {
            return -1;
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *tuple1_values[] = {NULL, NULL};
    const char *tuple2_values[] = {"alpha", NULL};
    const char *tuple3_values[] = {NULL, NULL, NULL};
    const char *tuple4_values[] = {"beta", "gamma"};
    Tuple tuples[] = {
        {tuple1_values, sizeof(tuple1_values) / sizeof(tuple1_values[0])},
        {tuple2_values, sizeof(tuple2_values) / sizeof(tuple2_values[0])},
        {tuple3_values, sizeof(tuple3_values) / sizeof(tuple3_values[0])},
        {tuple4_values, sizeof(tuple4_values) / sizeof(tuple4_values[0])}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (remove_all_none_tuples(tuples, &count) != 0) {
        fputs("Failed to remove tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_tuple_list(tuples, count) != 0 || fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}