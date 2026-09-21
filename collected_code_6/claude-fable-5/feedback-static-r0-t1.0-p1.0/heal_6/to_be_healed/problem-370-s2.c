#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 32

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_LEN];
    int id;
    float score;
} Tuple;

static int set_tuple_name(Tuple *tuple, const char *name)
{
    size_t len;

    if (tuple == NULL || name == NULL) {
        return -1;
    }

    len = strnlen(name, NAME_LEN);
    if (len >= NAME_LEN) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->name, name, len);
    tuple->name[len] = '\0';
    return 0;
}

static int init_tuple(Tuple *tuple, const char *name, int id, float score)
{
    if (tuple == NULL) {
        return -1;
    }
    if (set_tuple_name(tuple, name) != 0) {
        return -1;
    }
    tuple->id = id;
    tuple->score = score;
    return 0;
}

static int compare_by_float(const void *a, const void *b)
{
    const Tuple *t1 = (const Tuple *)a;
    const Tuple *t2 = (const Tuple *)b;

    if (t1->score < t2->score) {
        return -1;
    }
    if (t1->score > t2->score) {
        return 1;
    }
    return 0;
}

static int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0U) {
        return -1;
    }
    qsort(tuples, count, sizeof(Tuple), compare_by_float);
    return 0;
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        (void)printf("(%.*s, %d, %.2f)\n",
                     NAME_LEN - 1, tuples[i].name,
                     tuples[i].id, (double)tuples[i].score);
    }
}

int main(void)
{
    Tuple tuples[4];
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (init_tuple(&tuples[0], "alpha", 1, 3.14f) != 0 ||
        init_tuple(&tuples[1], "beta", 2, 1.41f) != 0 ||
        init_tuple(&tuples[2], "gamma", 3, 2.72f) != 0 ||
        init_tuple(&tuples[3], "delta", 4, 0.58f) != 0) {
        (void)fprintf(stderr, "Error: failed to initialize tuples\n");
        return EXIT_FAILURE;
    }

    (void)printf("Before sorting:\n");
    print_tuples(tuples, count);

    if (sort_tuples(tuples, count) != 0) {
        (void)fprintf(stderr, "Error: failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    (void)printf("After sorting:\n");
    print_tuples(tuples, count);

    return EXIT_SUCCESS;
}