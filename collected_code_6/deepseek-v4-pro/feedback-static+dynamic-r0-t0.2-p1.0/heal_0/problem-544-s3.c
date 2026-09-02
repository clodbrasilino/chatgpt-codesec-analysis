#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    int first;
    char *second;
} Tuple;

char *flatten_tuple_list(Tuple *tuples, int count) {
    size_t total_length = 0;
    int i;
    char *result;
    char *position;

    for (i = 0; i < count; i++) {
        total_length += snprintf(NULL, 0, "(%d, %s)", tuples[i].first, tuples[i].second);
    }

    result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    position = result;
    for (i = 0; i < count; i++) {
        int written = snprintf(position, total_length + 1 - (position - result), "(%d, %s)", tuples[i].first, tuples[i].second);
        if (written < 0) {
            free(result);
            return NULL;
        }
        position += written;
    }

    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, "apple"},
        {2, "banana"},
        {3, "cherry"}
    };
    int count = sizeof(tuples) / sizeof(tuples[0]);
    char *flattened = flatten_tuple_list(tuples, count);

    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    }

    return 0;
}