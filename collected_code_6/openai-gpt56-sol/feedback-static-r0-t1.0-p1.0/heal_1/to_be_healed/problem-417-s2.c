#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    /* Possible weaknesses found:
     *  struct member 'Tuple::second' is never used. [unusedStructMember]
     */
    int second;
} Tuple;

static bool find_common_first(const Tuple *tuples, size_t count, int *result)
{
    if (tuples == NULL || result == NULL || count == 0) {
        return false;
    }

    int candidate = tuples[0].first;

    for (size_t i = 1; i < count; ++i) {
        if (tuples[i].first != candidate) {
            return false;
        }
    }

    *result = candidate;
    return true;
}

int main(void)
{
    Tuple tuples[] = {
        {5, 10},
        {5, 20},
        {5, 30}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int common_first = 0;

    if (!find_common_first(tuples, count, &common_first)) {
        fputs("No common first element found.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", common_first) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}