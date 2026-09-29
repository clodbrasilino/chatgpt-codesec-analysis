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
    char buffer[64];
    /* Possible weaknesses found:
     *  The scope of the variable 'written' can be reduced. [variableScope]
     */
    int written;

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
        written = snprintf(buffer, sizeof(buffer), "%d %d", tuples[i].first, tuples[i].second);
        if (written < 0 || (size_t)written >= sizeof(buffer)) {
            free(result);
            return NULL;
        }

        while (length + (size_t)written + 2U > capacity) {
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
        }
        memcpy(&result[length], buffer, (size_t)written);
        length += (size_t)written;
        result[length] = '\0';
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