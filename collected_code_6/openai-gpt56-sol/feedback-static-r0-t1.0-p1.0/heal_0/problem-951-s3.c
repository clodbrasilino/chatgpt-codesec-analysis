#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

int maximum_similar_index(const Tuple *list1, size_t length1,
                          const Tuple *list2, size_t length2,
                          size_t *result)
{
    size_t common_length;

    if (result == NULL || (list1 == NULL && length1 > 0) ||
        (list2 == NULL && length2 > 0)) {
        return -1;
    }

    common_length = length1 < length2 ? length1 : length2;

    while (common_length > 0) {
        size_t index = common_length - 1;

        if (list1[index].first == list2[index].first &&
            list1[index].second == list2[index].second) {
            *result = index;
            return 1;
        }

        --common_length;
    }

    return 0;
}

int main(void)
{
    const Tuple list1[] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    };
    const Tuple list2[] = {
        {1, 2},
        {9, 10},
        {5, 6},
        {0, 0}
    };
    size_t result;
    int status = maximum_similar_index(
        list1,
        sizeof(list1) / sizeof(list1[0]),
        list2,
        sizeof(list2) / sizeof(list2[0]),
        &result
    );

    if (status < 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        puts("No similar indices found");
        return EXIT_SUCCESS;
    }

    if (printf("Maximum similar index: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}