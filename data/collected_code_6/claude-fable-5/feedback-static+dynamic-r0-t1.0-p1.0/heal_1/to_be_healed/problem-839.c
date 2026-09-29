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

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    return strcmp(ta->first, tb->first);
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
        if (printf("(%s, %d)\n", tuples[i].first, tuples[i].second) < 0) {
            break;
        }
    }
}

int main(void)
{
    Tuple tuples[] = {
        {"banana", 3},
        {"apple", 5},
        {"cherry", 1},
        {"date", 7},
        {"apricot", 2}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (sort_tuples(tuples, count) != 0) {
        if (fprintf(stderr, "Failed to sort tuples\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    print_tuples(tuples, count);

    return EXIT_SUCCESS;
}