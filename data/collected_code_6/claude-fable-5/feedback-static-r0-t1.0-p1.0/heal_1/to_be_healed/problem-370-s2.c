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
        (void)printf("(%s, %d, %.2f)\n",
                     tuples[i].name, tuples[i].id, (double)tuples[i].score);
    }
}

int main(void)
{
    Tuple tuples[] = {
        {"alpha", 1, 3.14f},
        {"beta", 2, 1.41f},
        {"gamma", 3, 2.72f},
        {"delta", 4, 0.58f}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

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