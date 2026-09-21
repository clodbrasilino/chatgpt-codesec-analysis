#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 64

typedef struct {
    char first[MAX_NAME_LEN];
    int second;
} Tuple;

static int set_tuple_name(Tuple *tuple, const char *name)
{
    size_t len;

    if (tuple == NULL || name == NULL) {
        return -1;
    }

    len = strnlen(name, MAX_NAME_LEN);
    if (len >= MAX_NAME_LEN) {
        return -1;
    }

    if (len >= sizeof(tuple->first)) {
        return -1;
    }

    memcpy(tuple->first, name, len);
    tuple->first[len] = '\0';
    return 0;
}

static int init_tuple(Tuple *tuple, const char *name, int value)
{
    if (tuple == NULL) {
        return -1;
    }
    if (set_tuple_name(tuple, name) != 0) {
        return -1;
    }
    tuple->second = value;
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
        if (printf("(%.*s, %d)\n", MAX_NAME_LEN, tuples[i].first,
                   tuples[i].second) < 0) {
            break;
        }
    }
}

int main(void)
{
    static const struct {
        const char *name;
        int value;
    } data[] = {
        {"banana", 3},
        {"apple", 5},
        {"cherry", 1},
        {"date", 7},
        {"apricot", 2}
    };
    size_t count = sizeof(data) / sizeof(data[0]);
    Tuple tuples[sizeof(data) / sizeof(data[0])];
    size_t i;

    memset(tuples, 0, sizeof(tuples));

    for (i = 0U; i < count; i++) {
        if (init_tuple(&tuples[i], data[i].name, data[i].value) != 0) {
            if (fprintf(stderr, "Failed to initialize tuple\n") < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
    }

    if (sort_tuples(tuples, count) != 0) {
        if (fprintf(stderr, "Failed to sort tuples\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    print_tuples(tuples, count);

    return EXIT_SUCCESS;
}