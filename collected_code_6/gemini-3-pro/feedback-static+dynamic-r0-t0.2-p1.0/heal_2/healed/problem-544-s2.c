#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

char* flatten_tuple_list(const Tuple* tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        char* empty_str = malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t buffer_size = count * 32 + 1; 
    char* result = malloc(buffer_size);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_length = 0;

    for (size_t i = 0; i < count; i++) {
        size_t remaining = buffer_size - current_length;
        
        int written = snprintf(result + current_length, remaining, "(%d, %d)%s", 
                               tuples[i].first, tuples[i].second, 
                               (i < count - 1) ? ", " : "");
        
        if (written < 0 || (size_t)written >= remaining) {
            free(result);
            return NULL;
        }

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
        fprintf(stderr, "Memory allocation failed or formatting error.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}