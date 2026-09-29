#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    int *items;
    size_t count;
} IntTuple;

IntTuple string_to_tuple(const char *str) {
    IntTuple tuple = {NULL, 0};
    if (str == NULL) {
        return tuple;
    }

    size_t capacity = 16;
    tuple.items = malloc(capacity * sizeof(int));
    if (tuple.items == NULL) {
        return tuple;
    }

    const char *ptr = str;
    while (*ptr != '\0') {
        char *end;
        errno = 0;
        long val = strtol(ptr, &end, 10);

        if (ptr == end) {
            ptr++;
            continue;
        }

        if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
            free(tuple.items);
            tuple.items = NULL;
            tuple.count = 0;
            return tuple;
        }

        if (tuple.count >= capacity) {
            capacity *= 2;
            int *temp = realloc(tuple.items, capacity * sizeof(int));
            if (temp == NULL) {
                free(tuple.items);
                tuple.items = NULL;
                tuple.count = 0;
                return tuple;
            }
            tuple.items = temp;
        }

        tuple.items[tuple.count] = (int)val;
        tuple.count++;
        ptr = end;
    }

    return tuple;
}

int main(void) {
    const char *input = "10, 20, 30, 40, 50";
    IntTuple t = string_to_tuple(input);

    if (t.items != NULL) {
        for (size_t i = 0; i < t.count; i++) {
            printf("%d ", t.items[i]);
        }
        printf("\n");
        free(t.items);
        t.items = NULL;
        /* Possible weaknesses found:
         *  Variable 't.count' is assigned a value that is never used. [unreadVariable]
         */
        t.count = 0;
    }

    return 0;
}