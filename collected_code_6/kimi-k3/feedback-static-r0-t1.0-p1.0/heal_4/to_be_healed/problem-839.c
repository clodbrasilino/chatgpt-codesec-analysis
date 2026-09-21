#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[MAX_STRING_LEN];
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    return strncmp(tuple_a->first, tuple_b->first, MAX_STRING_LEN);
}

void sort_tuples(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

int main(void) {
    Tuple tuples[] = {
        {"banana", 2},
        {"apple", 1},
        {"cherry", 3},
        {"date", 4}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        tuples[i].first[MAX_STRING_LEN - 1] = '\0';
    }

    printf("Original tuples:\n");
    for (i = 0; i < count; i++) {
        printf("(%s, %d)\n", tuples[i].first, tuples[i].second);
    }

    sort_tuples(tuples, count);

    printf("\nSorted tuples:\n");
    for (i = 0; i < count; i++) {
        printf("(%s, %d)\n", tuples[i].first, tuples[i].second);
    }

    return 0;
}