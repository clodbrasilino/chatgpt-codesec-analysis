#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

char *flatten_tuple_list(const Tuple *tuples, size_t count)
{
    size_t capacity;
    size_t length;
    size_t i;
    char *result;

    if (tuples == NULL || count == 0U) {
        result = malloc(1U);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    capacity = 64U;
    length = 0U;
    result = malloc(capacity);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    for (i = 0U; i < count; i++) {
        int needed = snprintf(NULL, 0U, "%d %d", tuples[i].first, tuples[i].second);
        size_t required;

        if (needed < 0) {
            free(result);
            return NULL;
        }

        required = length + (length > 0U ? 1U : 0U) + (size_t)needed + 1U;
        if (required < length) {
            free(result);
            return NULL;
        }

        while (required > capacity) {
            size_t new_capacity = capacity * 2U;
            char *tmp;

            if (new_capacity < capacity) {
                free(result);
                return NULL;
            }
            tmp = realloc(result, new_capacity);
            if (tmp == NULL) {
                free(result);
                return NULL;
            }
            result = tmp;
            capacity = new_capacity;
        }

        if (length > 0U) {
            result[length] = ' ';
            length++;
            result[length] = '\0';
        }

        {
            int written = snprintf(&result[length], capacity - length, "%d %d",
                                   tuples[i].first, tuples[i].second);
            if (written < 0 || (size_t)written >= capacity - length) {
                free(result);
                return NULL;
            }
            length += (size_t)written;
        }
    }

    return result;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    char *flattened;

    flattened = flatten_tuple_list(tuples, count);
    if (flattened == NULL) {
        fprintf(stderr, "Failed to flatten tuple list\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", flattened) < 0) {
        free(flattened);
        return EXIT_FAILURE;
    }

    free(flattened);
    return EXIT_SUCCESS;
}