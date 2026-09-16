#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Tuple {
    int first;
    int second;
};

bool find_common_first_element(struct Tuple* tuples, size_t size, int* common_first) {
    if (tuples == NULL || size == 0 || common_first == NULL) {
        return false;
    }

    *common_first = tuples[0].first;

    for (size_t i = 1; i < size; ++i) {
        if (tuples[i].first != *common_first) {
            return false;
        }
    }

    return true;
}

int main(void) {
    struct Tuple tuples[] = {
        {5, 10},
        {5, 20},
        {5, 30}
    };
    size_t size = sizeof(tuples) / sizeof(tuples[0]);
    int common_first;

    for (size_t i = 0; i < size; ++i) {
        printf("Tuple %zu: (%d, %d)\n", i, tuples[i].first, tuples[i].second);
    }

    if (find_common_first_element(tuples, size, &common_first)) {
        printf("%d\n", common_first);
    } else {
        printf("No common first element.\n");
    }

    struct Tuple tuples_diff[] = {
        {5, 10},
        {6, 20},
        {5, 30}
    };
    size = sizeof(tuples_diff) / sizeof(tuples_diff[0]);

    for (size_t i = 0; i < size; ++i) {
        printf("Tuple %zu: (%d, %d)\n", i, tuples_diff[i].first, tuples_diff[i].second);
    }

    if (find_common_first_element(tuples_diff, size, &common_first)) {
        printf("%d\n", common_first);
    } else {
        printf("No common first element.\n");
    }

    return 0;
}