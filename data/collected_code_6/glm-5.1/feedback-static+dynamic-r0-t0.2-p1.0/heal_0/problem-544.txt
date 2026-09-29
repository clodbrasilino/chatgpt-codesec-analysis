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

    size_t buffer_size = 1;
    for (size_t i = 0; i < count; i++) {
        buffer_size += snprintf(NULL, 0, "(%d,%d)", list[i].a, list[i].b);
        if (i < count - 1) {
            buffer_size += 1;
        }
    }

    char* result = (char*)malloc(buffer_size);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < count; i++) {
        int written = snprintf(result + offset, buffer_size - offset, "(%d,%d)", list[i].a, list[i].b);
        if (written < 0 || (size_t)written >= buffer_size - offset) {
            free(result);
            return NULL;
        }
        offset += written;
        if (i < count - 1) {
            result[offset] = ',';
            offset++;
            result[offset] = '\0';
        }
    }

    return result;
}

int main(void) {
    Tuple list[] = {{1, 2}, {3, 4}, {5, 6}};
    size_t count = sizeof(list) / sizeof(list[0]);

    char* flattened = flatten_tuple_list(list, count);
    if (flattened == NULL) {
        fprintf(stderr, "Failed to flatten tuple list\n");
        return 1;
    }

    printf("%s\n", flattened);

    free(flattened);
    flattened = NULL;

    return 0;
}