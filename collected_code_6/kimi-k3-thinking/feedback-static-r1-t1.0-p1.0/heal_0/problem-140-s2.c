#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int tuples_equal(Tuple a, Tuple b)
{
    return (a.first == b.first) && (a.second == b.second);
}

static size_t count_occurrences(const Tuple *list, size_t count, Tuple value)
{
    size_t occurrences = 0;
    size_t i;

    for (i = 0; i < count; i++) {
        if (tuples_equal(list[i], value)) {
            occurrences++;
        }
    }

    return occurrences;
}

size_t extract_singly_occurring(const Tuple *list, size_t count, Tuple **result)
{
    size_t singles_count = 0;
    size_t i;
    size_t j;
    Tuple *singles;

    if (result == NULL) {
        return 0;
    }

    *result = NULL;

    if (list == NULL || count == 0) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (count_occurrences(list, count, list[i]) == 1) {
            singles_count++;
        }
    }

    if (singles_count == 0) {
        return 0;
    }

    singles = malloc(singles_count * sizeof(*singles));
    if (singles == NULL) {
        return 0;
    }

    j = 0;
    for (i = 0; i < count; i++) {
        if (count_occurrences(list, count, list[i]) == 1) {
            singles[j] = list[i];
            j++;
        }
    }

    *result = singles;
    return singles_count;
}

int main(void)
{
    Tuple list[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4},
        {7, 8}
    };
    size_t count = sizeof(list) / sizeof(list[0]);
    Tuple *singles = NULL;
    size_t singles_count;
    size_t i;

    singles_count = extract_singly_occurring(list, count, &singles);

    printf("Singly occurring elements: ");
    for (i = 0; i < singles_count; i++) {
        printf("(%d, %d) ", singles[i].first, singles[i].second);
    }
    printf("\n");

    free(singles);

    return 0;
}