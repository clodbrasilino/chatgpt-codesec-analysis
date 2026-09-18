#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

char* flatten_tuple_list(Tuple* list, size_t size) {
    if (list == NULL || size == 0) {
        return NULL;
    }

    size_t buffer_size = size * 32;
    char* result = (char*)malloc(buffer_size);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_length = 0;

    for (size_t i = 0; i < size; i++) {
        char temp[32];
        int written = snprintf(temp, sizeof(temp), "(%d, %d)", list[i].a, list[i].b);
        
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
    Tuple list[] = {{1, 2}, {3, 4}, {5, 6}};
    size_t size = sizeof(list) / sizeof(list[0]);

    char* flattened = flatten_tuple_list(list, size);
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    } else {
        fprintf(stderr, "Failed to flatten tuple list.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}