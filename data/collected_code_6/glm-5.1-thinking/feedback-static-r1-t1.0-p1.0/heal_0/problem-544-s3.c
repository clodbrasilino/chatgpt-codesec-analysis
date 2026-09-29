#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

char *flatten_tuple_list(const Tuple *list, size_t count) {
    if (count == 0) {
        char *empty = malloc(3);
        if (!empty) return NULL;
        empty[0] = '[';
        empty[1] = ']';
        empty[2] = '\0';
        return empty;
    }

    size_t total_len = 2;
    for (size_t i = 0; i < count; i++) {
        int n = snprintf(NULL, 0, "(%d, %d)", list[i].first, list[i].second);
        if (n < 0) return NULL;
        total_len += (size_t)n;
        if (i < count - 1) {
            total_len += 2;
        }
    }
    total_len += 1;

    char *result = malloc(total_len);
    if (!result) return NULL;

    size_t offset = 0;
    result[offset++] = '[';

    for (size_t i = 0; i < count; i++) {
        int n = snprintf(result + offset, total_len - offset, "(%d, %d)", list[i].first, list[i].second);
        if (n < 0) {
            free(result);
            return NULL;
        }
        offset += (size_t)n;
        if (i < count - 1) {
            result[offset++] = ',';
            result[offset++] = ' ';
        }
    }

    result[offset++] = ']';
    result[offset] = '\0';

    return result;
}

int main(void) {
    Tuple list[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    size_t count = sizeof(list) / sizeof(list[0]);

    char *flattened = flatten_tuple_list(list, count);
    if (flattened) {
        printf("%s\n", flattened);
        free(flattened);
    }

    return 0;
}