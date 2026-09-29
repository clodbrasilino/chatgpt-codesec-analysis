#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 64

typedef struct {
    int id;
    char name[NAME_SIZE];
} Record;

typedef struct {
    Record record;
    int attribute;
} Tuple;

int find_max_attribute(const Tuple *tuples, size_t count, int *max_value) {
    if (tuples == NULL || count == 0 || max_value == NULL) {
        return -1;
    }

    *max_value = tuples[0].attribute;
    for (size_t i = 1; i < count; ++i) {
        if (tuples[i].attribute > *max_value) {
            *max_value = tuples[i].attribute;
        }
    }
    return 0;
}

int safe_copy_name(char *dest, size_t dest_size, const char *src) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }

    size_t src_len = strnlen(src, dest_size);
    if (src_len >= dest_size) {
        memcpy(dest, src, dest_size - 1);
        dest[dest_size - 1] = '\0';
        return -1;
    }

    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
    return 0;
}

int create_tuple(Tuple *t, int id, const char *name, int attribute) {
    if (t == NULL || name == NULL) {
        return -1;
    }

    t->record.id = id;
    if (safe_copy_name(t->record.name, NAME_SIZE, name) != 0) {
        return -1;
    }
    t->attribute = attribute;

    return 0;
}

int main(void) {
    Tuple tuples[4];
    size_t count = 4;
    int max_value = 0;

    if (create_tuple(&tuples[0], 1, "Alice", 25) != 0 ||
        create_tuple(&tuples[1], 2, "Bob", 42) != 0 ||
        create_tuple(&tuples[2], 3, "Charlie", 37) != 0 ||
        create_tuple(&tuples[3], 4, "Diana", 51) != 0) {
        fprintf(stderr, "Error: failed to create tuple\n");
        return EXIT_FAILURE;
    }

    if (find_max_attribute(tuples, count, &max_value) == 0) {
        printf("Maximum attribute value: %d\n", max_value);
    } else {
        fprintf(stderr, "Error: invalid input to find_max_attribute\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        printf("Record %d: %s, attribute: %d\n", 
               tuples[i].record.id, 
               tuples[i].record.name, 
               tuples[i].attribute);
    }

    return EXIT_SUCCESS;
}