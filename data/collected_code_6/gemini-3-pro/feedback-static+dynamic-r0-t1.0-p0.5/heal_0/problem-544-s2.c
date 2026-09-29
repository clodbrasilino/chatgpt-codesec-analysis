#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

char* flatten_tuple_list(Tuple* tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return NULL;
    }

    size_t buffer_size = count * 32;
    char* result = (char*)malloc(buffer_size);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_length = 0;

    for (size_t i = 0; i < count; i++) {
        char temp[32];
        int written = snprintf(temp, sizeof(temp), "(%d, %d)", tuples[i].first, tuples[i].second);
        
        if (written < 0 || (size_t)written >= sizeof(temp)) {
            free(result);
            return NULL;
        }

        if (current_length + written + 1 > buffer_size) {
            buffer_size *= 2;
            char* new_result = (char*)realloc(result, buffer_size);
            if (new_result == NULL) {
                free(result);
                return NULL;
            }
            result = new_result;
        }

        strncat(result, temp, buffer_size - current_length - 1);
        current_length += written;
    }

    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    char* flattened = flatten_tuple_list(tuples, count);
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    } else {
        fprintf(stderr, "Failed to flatten tuple list.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}