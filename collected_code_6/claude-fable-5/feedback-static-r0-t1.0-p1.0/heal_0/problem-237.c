#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple key;
    int count;
} Occurrence;

static Tuple normalize_tuple(Tuple t)
{
    Tuple result;
    if (t.first <= t.second) {
        result.first = t.first;
        result.second = t.second;
    } else {
        result.first = t.second;
        result.second = t.first;
    }
    return result;
}

int check_occurrences(const Tuple *tuples, size_t n, Occurrence *results,
                      size_t max_results, size_t *result_count)
{
    size_t i;
    size_t j;
    size_t count;

    if (tuples == NULL || results == NULL || result_count == NULL) {
        return -1;
    }

    count = 0;
    for (i = 0; i < n; i++) {
        Tuple norm = normalize_tuple(tuples[i]);
        int found = 0;
        for (j = 0; j < count; j++) {
            if (results[j].key.first == norm.first &&
                results[j].key.second == norm.second) {
                results[j].count++;
                found = 1;
                break;
            }
        }
        if (found == 0) {
            if (count >= max_results) {
                return -1;
            }
            results[count].key = norm;
            results[count].count = 1;
            count++;
        }
    }

    *result_count = count;
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {3, 1}, {1, 3}, {2, 5}, {5, 2}, {6, 3}
    };
    size_t n = sizeof(tuples) / sizeof(tuples[0]);
    Occurrence *results;
    size_t result_count = 0;
    size_t i;
    int status;

    results = (Occurrence *)malloc(n * sizeof(Occurrence));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = check_occurrences(tuples, n, results, n, &result_count);
    if (status != 0) {
        fprintf(stderr, "Error while counting occurrences\n");
        free(results);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; i++) {
        printf("(%d, %d): %d\n", results[i].key.first,
               results[i].key.second, results[i].count);
    }

    free(results);
    return EXIT_SUCCESS;
}