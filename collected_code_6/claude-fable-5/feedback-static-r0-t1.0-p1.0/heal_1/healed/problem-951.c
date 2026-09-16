#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int max_similar_indices(const Tuple *list1, const Tuple *list2, size_t len, Tuple *result)
{
    size_t i;

    if (list1 == NULL || list2 == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        result[i].first = (list1[i].first > list2[i].first) ? list1[i].first : list2[i].first;
        result[i].second = (list1[i].second > list2[i].second) ? list1[i].second : list2[i].second;
    }

    return 0;
}

int main(void)
{
    const Tuple list1[] = { {3, 5}, {6, 7}, {4, 11} };
    const Tuple list2[] = { {5, 4}, {8, 6}, {2, 12} };
    size_t len = sizeof(list1) / sizeof(list1[0]);
    Tuple *result;
    size_t i;
    int status;

    result = malloc(len * sizeof(Tuple));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = max_similar_indices(list1, list2, len, result);
    if (status != 0) {
        fprintf(stderr, "Invalid input to max_similar_indices\n");
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < len; i++) {
        if (printf("(%d, %d)\n", result[i].first, result[i].second) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}