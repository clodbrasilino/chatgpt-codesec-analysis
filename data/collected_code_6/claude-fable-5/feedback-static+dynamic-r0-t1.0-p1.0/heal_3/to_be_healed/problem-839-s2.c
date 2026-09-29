#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[MAX_NAME_LEN];
    int second;
} Tuple;

static int set_tuple(Tuple *t, const char *name, int value)
{
    size_t len;

    if (t == NULL || name == NULL) {
        return -1;
    }

    len = strnlen(name, MAX_NAME_LEN);
    if (len >= MAX_NAME_LEN) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(t->first, name, len);
    t->first[len] = '\0';
    t->second = value;
    return 0;
}

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    return strncmp(ta->first, tb->first, MAX_NAME_LEN);
}

static int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0U) {
        return -1;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    return 0;
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;
    if (tuples == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        (void)printf("(%.*s, %d)\n", MAX_NAME_LEN, tuples[i].first, tuples[i].second);
    }
}

int main(void)
{
    Tuple tuples[5];
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (set_tuple(&tuples[0], "banana", 3) != 0 ||
        set_tuple(&tuples[1], "apple", 5) != 0 ||
        set_tuple(&tuples[2], "cherry", 1) != 0 ||
        set_tuple(&tuples[3], "date", 7) != 0 ||
        set_tuple(&tuples[4], "apricot", 2) != 0) {
        (void)fprintf(stderr, "Error: failed to initialize tuples\n");
        return EXIT_FAILURE;
    }

    if (sort_tuples(tuples, count) != 0) {
        (void)fprintf(stderr, "Error: failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    print_tuples(tuples, count);

    return EXIT_SUCCESS;
}