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

    for (size_t i = 0; i < count; i++) {
        if (i > 0) {
            if (length + 2 >= capacity) {
                capacity *= 2;
                char* temp = realloc(buffer, capacity);
                if (temp == NULL) {
                    free(buffer);
                    return NULL;
                }
                buffer = temp;
            }
            buffer[length++] = ',';
            buffer[length++] = ' ';
        }

        int needed = snprintf(NULL, 0, "(%d, %d)", list[i].a, list[i].b);
        if (needed < 0) {
            free(buffer);
            return NULL;
        }

        while (length + (size_t)needed >= capacity) {
            capacity *= 2;
            char* temp = realloc(buffer, capacity);
            if (temp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        snprintf(buffer + length, capacity - length, "(%d, %d)", list[i].a, list[i].b);
        length += needed;
    }

    if (length >= capacity) {
        capacity = length + 1;
        char* temp = realloc(buffer, capacity);
        if (temp == NULL) {
            free(buffer);
            return NULL;
        }
        buffer = temp;
    }

    buffer[length] = '\0';

    char* result = realloc(buffer, length + 1);
    return result != NULL ? result : buffer;
}

int main(void) {
    Tuple list[] = {{1, 2}, {3, 4}, {5, 6}};
    size_t count = sizeof(list) / sizeof(list[0]);

    char* flattened = flatten_tuple_list(list, count);
    if (flattened == NULL) {
        return 1;
    }

    printf("%s\n", flattened);

    free(flattened);
    flattened = NULL;

    return 0;
}