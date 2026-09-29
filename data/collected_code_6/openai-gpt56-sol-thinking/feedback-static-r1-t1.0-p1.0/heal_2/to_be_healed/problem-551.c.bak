#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const int *values;
    size_t length;
} IntList;

static int extract_column(const IntList *lists, size_t list_count, size_t column,
                          int **result, size_t *result_count)
{
    int *column_values;
    size_t i;

    if (result == NULL || result_count == NULL) {
        return EINVAL;
    }

    *result = NULL;
    *result_count = 0;

    if (list_count == 0) {
        return 0;
    }

    if (lists == NULL) {
        return EINVAL;
    }

    if (list_count > SIZE_MAX / sizeof(*column_values)) {
        return ERANGE;
    }

    for (i = 0; i < list_count; ++i) {
        if (lists[i].values == NULL || column >= lists[i].length) {
            return ERANGE;
        }
    }

    column_values = malloc(list_count * sizeof(*column_values));
    if (column_values == NULL) {
        return ENOMEM;
    }

    for (i = 0; i < list_count; ++i) {
        column_values[i] = lists[i].values[column];
    }

    *result = column_values;
    *result_count = list_count;

    return 0;
}

static int parse_column(const char *text, size_t *column)
{
    char *end;
    uintmax_t value;

    if (text == NULL || column == NULL || text[0] == '\0' || text[0] == '-') {
        return EINVAL;
    }

    errno = 0;
    value = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || value > SIZE_MAX) {
        return ERANGE;
    }

    *column = (size_t)value;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    static const int first[] = {1, 2, 3};
    static const int second[] = {4, 5, 6};
    static const int third[] = {7, 8, 9};
    static const IntList nested_list[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    int *column_values = NULL;
    size_t result_count = 0;
    size_t column = 1;
    size_t i;
    int status;

    if (argc > 2) {
        (void)fprintf(stderr, "Usage: %s [column]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        status = parse_column(argv[1], &column);
        if (status != 0) {
            (void)fprintf(stderr, "Invalid column: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    status = extract_column(
        nested_list,
        sizeof(nested_list) / sizeof(nested_list[0]),
        column,
        &column_values,
        &result_count
    );

    if (status != 0) {
        (void)fprintf(stderr, "Unable to extract column: %s\n",
                      strerror(status));
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; ++i) {
        if (i != 0 && putchar(' ') == EOF) {
            free(column_values);
            return EXIT_FAILURE;
        }

        if (printf("%d", column_values[i]) < 0) {
            free(column_values);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(column_values);
        return EXIT_FAILURE;
    }

    free(column_values);
    return EXIT_SUCCESS;
}