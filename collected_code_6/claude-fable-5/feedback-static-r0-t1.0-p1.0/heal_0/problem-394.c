#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_distinct(const int *tuple, size_t length)
{
    size_t i;
    size_t j;

    if (tuple == NULL) {
        return false;
    }

    for (i = 0; i < length; i++) {
        for (j = i + 1; j < length; j++) {
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
    int tuple3[] = {2, 3, 4, 5, 6};
    size_t len1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t len2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t len3 = sizeof(tuple3) / sizeof(tuple3[0]);

    if (is_distinct(tuple1, len1)) {
        printf("Tuple 1 is distinct\n");
    } else {
        printf("Tuple 1 is not distinct\n");
    }

    if (is_distinct(tuple2, len2)) {
        printf("Tuple 2 is distinct\n");
    } else {
        printf("Tuple 2 is not distinct\n");
    }

    if (is_distinct(tuple3, len3)) {
        printf("Tuple 3 is distinct\n");
    } else {
        printf("Tuple 3 is not distinct\n");
    }

    return 0;
}