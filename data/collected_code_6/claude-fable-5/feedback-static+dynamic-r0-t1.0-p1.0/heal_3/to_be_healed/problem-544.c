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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];

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
        int written = snprintf(buffer, sizeof(buffer), "%d %d",
                               tuples[i].first, tuples[i].second);
        size_t needed;

        if (written < 0 || (size_t)written >= sizeof(buffer)) {
            free(result);
            return NULL;
        }

        needed = (size_t)written;
        if (needed > (size_t)-1 - length - 2U) {
            free(result);
            return NULL;
        }

        while (length + needed + 2U > capacity) {
            size_t new_capacity;
            char *tmp;

            if (capacity > (size_t)-1 / 2U) {
                free(result);
                return NULL;
            }
            new_capacity = capacity * 2U;
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

        if (length + needed + 1U > capacity) {
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(&result[length], buffer, needed);
        length += needed;
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