#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int convert_tuple_to_int(const int *tuple, size_t size) {
    int result = 0;

    if (tuple == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] < 0 || tuple[i] > 9) {
            return 0;
        }

        if (result > (INT_MAX - tuple[i]) / 10) {
            return 0;
        }

        result = result * 10 + tuple[i];
    }

    return result;
}

int main(void) {
    int tuple1[] = {1, 2, 3, 4};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int res1 = convert_tuple_to_int(tuple1, size1);
    printf("%d\n", res1);

    int tuple2[] = {0, 5, 9};
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    int res2 = convert_tuple_to_int(tuple2, size2);
    printf("%d\n", res2);

    int res3 = convert_tuple_to_int(NULL, size2);
    printf("%d\n", res3);

    return 0;
}