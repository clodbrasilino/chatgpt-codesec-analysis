#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[64];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second[64];
} Tuple;

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
    Tuple tuples[] = {
        {"banana", "yellow"},
        {"apple", "red"},
        {"cherry", "dark red"},
        {"date", "brown"}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;

    if (sort_tuples(tuples, count) != 0) {
        fprintf(stderr, "Error: failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("%s: %s\n", tuples[i].first, tuples[i].second);
    }

    return EXIT_SUCCESS;
}