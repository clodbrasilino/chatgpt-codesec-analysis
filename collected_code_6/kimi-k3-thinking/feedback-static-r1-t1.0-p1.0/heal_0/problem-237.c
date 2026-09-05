#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

static bool tuples_equal(const Tuple *a, const Tuple *b)
{
    return (a->first == b->first) && (a->second == b->second);
}

int check_similar_occurrences(const Tuple tuples[], size_t size)
{
    size_t i;
    size_t j;
    size_t reference_count = 0u;
    bool reference_set = false;

    if (tuples == NULL) {
        return -1;
    }
    if (size == 0u) {
        return -1;
    }

    for (i = 0u; i < size; i++) {
        bool seen_before = false;
        size_t count = 0u;

        for (j = 0u; j < i; j++) {
            if (tuples_equal(&tuples[i], &tuples[j])) {
                seen_before = true;
                break;
            }
        }
        if (seen_before) {
            continue;
        }

        for (j = 0u; j < size; j++) {
            if (tuples_equal(&tuples[i], &tuples[j])) {
                count++;
            }
        }

        if (!reference_set) {
            reference_count = count;
            reference_set = true;
        } else if (count != reference_count) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    const Tuple tuples1[] = {{1, 2}, {3, 4}, {1, 2}, {3, 4}, {5, 6}, {5, 6}};
    const Tuple tuples2[] = {{1, 2}, {3, 4}, {1, 2}, {3, 4}, {5, 6}};
    const size_t size1 = sizeof(tuples1) / sizeof(tuples1[0]);
    const size_t size2 = sizeof(tuples2) / sizeof(tuples2[0]);
    int result;

    result = check_similar_occurrences(tuples1, size1);
    if (result < 0) {
        fprintf(stderr, "Error: invalid input for test 1\n");
        return 1;
    }
    printf("Test 1: %s\n", (result == 1) ? "Similar occurrences" : "Not similar occurrences");

    result = check_similar_occurrences(tuples2, size2);
    if (result < 0) {
        fprintf(stderr, "Error: invalid input for test 2\n");
        return 1;
    }
    printf("Test 2: %s\n", (result == 1) ? "Similar occurrences" : "Not similar occurrences");

    result = check_similar_occurrences(NULL, 0u);
    if (result < 0) {
        printf("Test 3: Invalid input handled correctly\n");
    } else {
        fprintf(stderr, "Error: invalid input not detected\n");
        return 1;
    }

    return 0;
}