#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    size_t capacity = 0;
    const char *ptr = str;

    while (*ptr != '\0') {
        char *endptr;
        errno = 0;
        long val = strtol(ptr, &endptr, 10);

        if (ptr == endptr) {
            ptr++;
            continue;
        }

        if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
            ptr = endptr;
            continue;
        }

        if (tuple.count >= capacity) {
            size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
            int *new_items = realloc(tuple.items, new_capacity * sizeof(int));
            if (new_items == NULL) {
                free(tuple.items);
                tuple.items = NULL;
                tuple.count = 0;
                return tuple;
            }
            tuple.items = new_items;
            capacity = new_capacity;
        }

        tuple.items[tuple.count] = (int)val;
        tuple.count++;
        ptr = endptr;
    }

    if (tuple.count == 0) {
        free(tuple.items);
        tuple.items = NULL;
    } else {
        int *shrunk = realloc(tuple.items, tuple.count * sizeof(int));
        if (shrunk != NULL) {
            tuple.items = shrunk;
        }
    }

    return tuple;
}

int main(void) {
    const char *input = "10, 20, -5, 100, 0";
    IntTuple t = string_to_tuple(input);
    
    printf("(");
    for (size_t i = 0; i < t.count; i++) {
        printf("%d", t.items[i]);
        if (i < t.count - 1) {
            printf(", ");
        }
    }
    printf(")\n");
    
    free(t.items);
    
    return 0;
}