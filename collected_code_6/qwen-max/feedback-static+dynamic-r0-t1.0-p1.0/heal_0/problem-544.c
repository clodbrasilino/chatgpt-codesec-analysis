#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TUPLES 100
#define TUPLE_SIZE 2
#define BUFFER_SIZE 500

typedef struct {
    int id;
    double value;
} Tuple;

char* flatten_tuple_list(Tuple *tuples, int count) {
    char *buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        return NULL;
    }
    int offset = 0;

    for (int i = 0; i < count; i++) {
        int written = snprintf(buffer + offset, BUFFER_SIZE - offset, "[%d, %.2f] ", tuples[i].id, tuples[i].value);
        if (written < 0 || (size_t)written >= BUFFER_SIZE - offset) {
            free(buffer);
            return NULL;
        }
        offset += written;
    }

    buffer[offset - 1] = '\0'; // Remove the last space
    return buffer;
}

int main() {
    Tuple tuples[MAX_TUPLES] = {
        {1, 1.1},
        {2, 2.2},
        {3, 3.3}
    };
    int count = 3;

    char *flattened = flatten_tuple_list(tuples, count);
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    } else {
        fprintf(stderr, "Failed to flatten tuple list.\n");
    }

    return 0;
}