#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NAME_LEN 32

typedef struct {
    char name[NAME_LEN];
    int value;
} Tuple;

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;

    if (ta->value < tb->value) {
        return -1;
    }
    if (ta->value > tb->value) {
        return 1;
    }
    return 0;
}

static int set_tuple(Tuple *t, const char *name, int value)
{
    size_t len;

    if (t == NULL || name == NULL) {
        return -1;
    }

    len = strnlen(name, NAME_LEN);
    if (len >= NAME_LEN) {
        return -1;
    }

    memcpy(t->name, name, len);
    t->name[len] = '\0';
    t->value = value;

    return 0;
}

static Tuple *find_min_k_records(const Tuple *records, size_t n, size_t k)
{
    Tuple *sorted;
    Tuple *result;

    if (records == NULL || n == 0U || k == 0U || k > n) {
        return NULL;
    }

    if (n > SIZE_MAX / sizeof(*sorted)) {
        return NULL;
    }

    sorted = malloc(n * sizeof(*sorted));
    if (sorted == NULL) {
        return NULL;
    }

    memcpy(sorted, records, n * sizeof(*sorted));
    qsort(sorted, n, sizeof(*sorted), compare_tuples);

    result = malloc(k * sizeof(*result));
    if (result == NULL) {
        free(sorted);
        return NULL;
    }

    memcpy(result, sorted, k * sizeof(*result));
    free(sorted);

    return result;
}

int main(void)
{
    Tuple records[6];
    size_t n = sizeof(records) / sizeof(records[0]);
    size_t k = 3U;
    Tuple *min_records;
    size_t i;

    if (set_tuple(&records[0], "Alice", 45) != 0 ||
        set_tuple(&records[1], "Bob", 12) != 0 ||
        set_tuple(&records[2], "Carol", 78) != 0 ||
        set_tuple(&records[3], "Dave", 3) != 0 ||
        set_tuple(&records[4], "Eve", 56) != 0 ||
        set_tuple(&records[5], "Frank", 23) != 0) {
        fprintf(stderr, "Failed to initialize records\n");
        return EXIT_FAILURE;
    }

    min_records = find_min_k_records(records, n, k);
    if (min_records == NULL) {
        fprintf(stderr, "Failed to find minimum records\n");
        return EXIT_FAILURE;
    }

    printf("Minimum %zu records:\n", k);
    for (i = 0U; i < k; i++) {
        printf("%.*s: %d\n", NAME_LEN, min_records[i].name, min_records[i].value);
    }

    free(min_records);

    return EXIT_SUCCESS;
}