#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool check_valid(const int *tuple, size_t size)
{
    if (tuple == NULL || size == 0) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int tuple1[] = {1, 1, 1, 1};
    int tuple2[] = {1, 0, 1, 1};
    int tuple3[] = {1, 1, 1};

    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t size3 = sizeof(tuple3) / sizeof(tuple3[0]);

    if (check_valid(tuple1, size1)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    if (check_valid(tuple2, size2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    if (check_valid(tuple3, size3)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    if (check_valid(NULL, 0)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}