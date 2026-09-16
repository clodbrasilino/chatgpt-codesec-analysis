#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_distinct(const int *tuple, size_t size)
{
    size_t i;
    size_t j;

    if (tuple == NULL) {
        return false;
    }

    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (tuple[i] == tuple[j]) {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    int tuple1[] = {1, 4, 5, 6, 1, 4};
    int tuple2[] = {1, 4, 5, 6};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    if (is_distinct(tuple1, size1)) {
        if (printf("Tuple 1 is distinct\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Tuple 1 is not distinct\n") < 0) {
            return 1;
        }
    }

    if (is_distinct(tuple2, size2)) {
        if (printf("Tuple 2 is distinct\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Tuple 2 is not distinct\n") < 0) {
            return 1;
        }
    }

    return 0;
}