#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 64

typedef struct {
    char first[MAX_NAME_LEN];
    int second;
} Tuple;

static int set_tuple(Tuple *tuple, const char *name, int value)
{
    size_t len;

    if (tuple == NULL || name == NULL) {
        return -1;
    }

    len = strnlen(name, MAX_NAME_LEN);
    if (len >= MAX_NAME_LEN) {
        return -1;
    }

    memcpy(tuple->first, name, len);
    tuple->first[len] = '\0';
    tuple->second = value;
    return 0;
}

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    return strncmp(ta->first, tb->first, MAX_NAME_LEN);
}

static void sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0U) {
        return;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

static int print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        if (printf("(%.*s, %d)\n", MAX_NAME_LEN, tuples[i].first,
                   tuples[i].second) < 0) {
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    static const struct {
        const char *name;
        int value;
    } data[] = {
        { "banana", 3 },
        { "apple", 5 },
        { "cherry", 1 },
        { "date", 7 },
        { "apricot", 2 }
    };
    size_t count = sizeof(data) / sizeof(data[0]);
    Tuple tuples[sizeof(data) / sizeof(data[0])];
    size_t i;

    for (i = 0U; i < count; i++) {
        if (set_tuple(&tuples[i], data[i].name, data[i].value) != 0) {
            (void)fprintf(stderr, "Initialization error\n");
            return EXIT_FAILURE;
        }
    }

    sort_tuples(tuples, count);

    if (print_tuples(tuples, count) != 0) {
        (void)fprintf(stderr, "Output error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}