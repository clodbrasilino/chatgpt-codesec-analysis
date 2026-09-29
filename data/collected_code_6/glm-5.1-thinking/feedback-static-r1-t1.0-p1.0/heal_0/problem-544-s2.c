#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

char *flatten_tuple_list(const Tuple *list, size_t count) {
    if (list == NULL || count == 0) {
        char *empty_str = malloc(1);
        if (empty_str == NULL) {
            return NULL;
        }
        empty_str[0] = '\0';
        return empty_str;
    }

    size_t length = 0;
    for (size_t i = 0; i < count; i++) {
        int n = snprintf(NULL, 0, "(%d, %d)", list[i].first, list[i].second);
        if (n < 0) {
            return NULL;
        }
        length += (size_t)n;
        if (i < count - 1) {
            length += 2;
        }
    }

    char *result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < count; i++) {
        int n = snprintf(result + offset, length + 1 - offset, "(%d, %d)", list[i].first, list[i].second);
        if (n < 0 || (size_t)n >= length + 1 - offset) {
            free(result);
            return NULL;
        }
        offset += (size_t)n;
        if (i < count - 1) {
            result[offset++] = ',';
            result[offset++] = ' ';
        }
    }

    result[length] = '\0';
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
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    }

    char *empty = flatten_tuple_list(NULL, 0);
    if (empty != NULL) {
        printf("%s\n", empty);
        free(empty);
    }

    return 0;
}