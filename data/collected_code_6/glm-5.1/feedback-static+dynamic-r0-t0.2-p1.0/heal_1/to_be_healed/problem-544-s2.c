#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

char* flatten_tuple_list(Tuple* list, size_t count) {
    if (list == NULL && count > 0) {
        return NULL;
    }

    size_t capacity = 64;
    char* buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    size_t length = 0;
    buffer[0] = '\0';

    for (size_t i = 0; i < count; i++) {
        int written;
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char temp[64];

        if (i == 0) {
            written = snprintf(temp, sizeof(temp), "(%d, %d)", list[i].a, list[i].b);
        } else {
            written = snprintf(temp, sizeof(temp), ", (%d, %d)", list[i].a, list[i].b);
        }

        if (written < 0) {
            free(buffer);
            return NULL;
        }

        size_t temp_len = (size_t)written;
        while (length + temp_len + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }
            char* new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer + length, temp, temp_len + 1);
        length += temp_len;
    }

    char* result = realloc(buffer, length + 1);
    if (result != NULL) {
        buffer = result;
    }

    return buffer;
}

int main(void) {
    Tuple list[] = {{1, 2}, {3, 4}, {5, 6}};
    size_t count = sizeof(list) / sizeof(list[0]);

    char* flattened = flatten_tuple_list(list, count);
    if (flattened == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", flattened);

    free(flattened);
    flattened = NULL;

    return EXIT_SUCCESS;
}