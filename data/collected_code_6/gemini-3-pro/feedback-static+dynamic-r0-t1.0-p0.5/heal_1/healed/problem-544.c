#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
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
        int needed = snprintf(NULL, 0, "(%d, %d)", tuples[i].a, tuples[i].b);
        
        if (needed < 0) {
            free(result);
            return NULL;
        }

        if (current_length + (size_t)needed + 1 > buffer_size) {
            while (current_length + (size_t)needed + 1 > buffer_size) {
                buffer_size *= 2;
            }
            char* new_result = (char*)realloc(result, buffer_size);
            if (new_result == NULL) {
                free(result);
                return NULL;
            }
            result = new_result;
        }

        snprintf(result + current_length, buffer_size - current_length, "(%d, %d)", tuples[i].a, tuples[i].b);
        current_length += (size_t)needed;
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