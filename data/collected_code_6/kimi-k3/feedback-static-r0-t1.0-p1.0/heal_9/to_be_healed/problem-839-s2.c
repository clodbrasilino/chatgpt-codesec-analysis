#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TUPLE_STR_SIZE 64

typedef struct {
    char *first;
    char *second;
} Tuple;

static int copy_string(char **dest, const char *src)
{
    size_t src_len;
    char *new_str;

    if (dest == NULL || src == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    src_len = strlen(src);
    new_str = malloc(src_len + 1);
    if (new_str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_str, src, src_len + 1);
    *dest = new_str;
    return 0;
}

static int init_tuple(Tuple *tuple, const char *first, const char *second)
{
    if (tuple == NULL) {
        return -1;
    }

    tuple->first = NULL;
    tuple->second = NULL;

    if (copy_string(&tuple->first, first) != 0) {
        return -1;
    }

    if (copy_string(&tuple->second, second) != 0) {
        free(tuple->first);
        tuple->first = NULL;
        return -1;
    }

    return 0;
}

static void free_tuple(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }
    free(tuple->first);
    free(tuple->second);
    tuple->first = NULL;
    tuple->second = NULL;
}

int compare_tuples(const void *a, const void *b)
{
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;

    return strcmp(tuple_a->first, tuple_b->first);
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
        for (i = 0; i < count; i++) {
            free_tuple(&tuples[i]);
        }
        return EXIT_FAILURE;
    }

    if (sort_tuples(tuples, count) != 0) {
        fprintf(stderr, "Error: failed to sort tuples\n");
        for (i = 0; i < count; i++) {
            free_tuple(&tuples[i]);
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("%s: %s\n", tuples[i].first, tuples[i].second);
    }

    for (i = 0; i < count; i++) {
        free_tuple(&tuples[i]);
    }

    return EXIT_SUCCESS;
}