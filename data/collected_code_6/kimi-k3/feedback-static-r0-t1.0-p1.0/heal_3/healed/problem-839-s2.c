#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TUPLE_STR_SIZE 64

typedef struct {
    char first[TUPLE_STR_SIZE];
    char second[TUPLE_STR_SIZE];
} Tuple;

static int copy_string(char *dest, size_t dest_size, const char *src)
{
    size_t src_len;

    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }

    src_len = strnlen(src, dest_size - 1);
    if (src_len >= dest_size - 1) {
        return -1;
    }

    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
    return 0;
}

static int init_tuple(Tuple *tuple, const char *first, const char *second)
{
    if (tuple == NULL) {
        return -1;
    }

    if (copy_string(tuple->first, sizeof(tuple->first), first) != 0) {
        return -1;
    }

    if (copy_string(tuple->second, sizeof(tuple->second), second) != 0) {
        return -1;
    }

    return 0;
}

int compare_tuples(const void *a, const void *b)
{
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;

    return strncmp(tuple_a->first, tuple_b->first, TUPLE_STR_SIZE);
}

int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0) {
        return -1;
    }

    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    return 0;
}

int main(void)
{
    Tuple tuples[4];
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;

    if (init_tuple(&tuples[0], "banana", "yellow") != 0 ||
        init_tuple(&tuples[1], "apple", "red") != 0 ||
        init_tuple(&tuples[2], "cherry", "dark red") != 0 ||
        init_tuple(&tuples[3], "date", "brown") != 0) {
        fprintf(stderr, "Error: failed to initialize tuples\n");
        return EXIT_FAILURE;
    }

    if (sort_tuples(tuples, count) != 0) {
        fprintf(stderr, "Error: failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("%s: %s\n", tuples[i].first, tuples[i].second);
    }

    return EXIT_SUCCESS;
}