#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_distinct(const int *tuple, size_t size) {
    if (tuple == NULL || size == 0) {
        return true;
    }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (tuple[i] == tuple[j]) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    int tuple1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    if (is_distinct(tuple1, size1)) {
        printf("tuple1 is distinct\n");
    } else {
        printf("tuple1 is not distinct\n");
    }

    int tuple2[] = {1, 2, 3, 2, 5};
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    if (is_distinct(tuple2, size2)) {
        printf("tuple2 is distinct\n");
    } else {
        printf("tuple2 is not distinct\n");
    }

    return EXIT_SUCCESS;
}