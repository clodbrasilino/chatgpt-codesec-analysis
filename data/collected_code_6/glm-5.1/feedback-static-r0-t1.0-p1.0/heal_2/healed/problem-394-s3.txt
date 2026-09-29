#include <stdio.h>
#include <stdlib.h>

int is_distinct(const int *tuple, size_t size) {
    if (size == 0) {
        return 1;
    }
    if (tuple == NULL) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (tuple[i] == tuple[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void) {
    int tuple1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int result1 = is_distinct(tuple1, size1);
    printf("%d\n", result1);

    int tuple2[] = {1, 2, 3, 2, 5};
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    int result2 = is_distinct(tuple2, size2);
    printf("%d\n", result2);

    const int *tuple3 = NULL;
    size_t size3 = 0;
    int result3 = is_distinct(tuple3, size3);
    printf("%d\n", result3);

    return 0;
}