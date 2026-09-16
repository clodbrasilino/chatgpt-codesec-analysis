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

void print_result(const int *tuple, size_t size)
{
    bool result = check_valid(tuple, size);

    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }
}

int main(void)
{
    int tuple1[] = {1, 1, 1, 1};
    int tuple2[] = {1, 0, 1, 1};
    int tuple3[] = {1, 1, 1};
    const int *tuple4 = NULL;

    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t size3 = sizeof(tuple3) / sizeof(tuple3[0]);
    size_t size4 = 0;

    print_result(tuple1, size1);
    print_result(tuple2, size2);
    print_result(tuple3, size3);
    print_result(tuple4, size4);

    return 0;
}