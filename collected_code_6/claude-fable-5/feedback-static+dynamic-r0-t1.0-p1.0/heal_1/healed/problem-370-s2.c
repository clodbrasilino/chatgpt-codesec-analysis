#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 32

typedef struct {
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
    len = strlen(name);
    if (len >= NAME_LEN) {
        return -1;
    }
    memcpy(tuple->name, name, len);
    tuple->name[len] = '\0';
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
                     NAME_LEN - 1,
                     tuples[i].name,
                     tuples[i].id,
                     (double)tuples[i].score);
    }
}

int main(void)
{
    Tuple tuples[4];
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    memset(tuples, 0, sizeof(tuples));

    if (set_tuple_name(&tuples[0], "alpha") != 0 ||
        set_tuple_name(&tuples[1], "beta") != 0 ||
        set_tuple_name(&tuples[2], "gamma") != 0 ||
        set_tuple_name(&tuples[3], "delta") != 0) {
        (void)fprintf(stderr, "Error: failed to initialize tuple names\n");
        return EXIT_FAILURE;
    }

    tuples[0].id = 1;
    tuples[0].score = 3.14f;
    tuples[1].id = 2;
    tuples[1].score = 1.41f;
    tuples[2].id = 3;
    tuples[2].score = 2.72f;
    tuples[3].id = 4;
    tuples[3].score = 0.58f;

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