#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int max_similar_index(const Tuple *list1, size_t length1,
                             const Tuple *list2, size_t length2,
                             size_t *result)
{
    size_t limit;

    if (result == NULL || (length1 > 0 && list1 == NULL) ||
        (length2 > 0 && list2 == NULL)) {
        return -1;
    }

    limit = length1 < length2 ? length1 : length2;

    for (size_t i = limit; i > 0; --i) {
        size_t index = i - 1;

        if (list1[index].first == list2[index].first &&
            list1[index].second == list2[index].second) {
            *result = index;
            return 1;
        }
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
        {0, 4},
        {5, 6},
        {9, 8}
    };
    const size_t length1 = sizeof(list1) / sizeof(list1[0]);
    const size_t length2 = sizeof(list2) / sizeof(list2[0]);
    size_t index = 0;
    int status = max_similar_index(list1, length1, list2, length2, &index);

    if (status < 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        puts("No similar index found");
        return EXIT_SUCCESS;
    }

    if (printf("Maximum similar index: %zu\n", index) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}