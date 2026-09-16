#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_greater(const int *tuple1, const int *tuple2, size_t length)
{
    if (tuple1 == NULL || tuple2 == NULL || length == 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; i++) {
        if (tuple2[i] <= tuple1[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int first_tuple[] = {10, 4, 5};
    const int second_tuple[] = {13, 5, 18};
    size_t length = sizeof(first_tuple) / sizeof(first_tuple[0]);

    bool result = check_greater(first_tuple, second_tuple, length);

    if (result) {
        if (printf("True\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("False\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    const int first_tuple2[] = {1, 2, 3};
    const int second_tuple2[] = {2, 1, 4};
    size_t length2 = sizeof(first_tuple2) / sizeof(first_tuple2[0]);

    result = check_greater(first_tuple2, second_tuple2, length2);

    if (result) {
        if (printf("True\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("False\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}