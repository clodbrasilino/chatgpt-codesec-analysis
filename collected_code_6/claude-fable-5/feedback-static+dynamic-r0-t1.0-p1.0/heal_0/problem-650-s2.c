#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool arrays_are_equal(const int *arr1, size_t len1, const int *arr2, size_t len2)
{
    if (arr1 == NULL || arr2 == NULL) {
        return false;
    }

    if (len1 != len2) {
        return false;
    }

    for (size_t i = 0; i < len1; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int first[] = {1, 2, 3, 4, 5};
    int second[] = {1, 2, 3, 4, 5};
    int third[] = {1, 2, 3, 4, 6};

    size_t first_len = sizeof(first) / sizeof(first[0]);
    size_t second_len = sizeof(second) / sizeof(second[0]);
    size_t third_len = sizeof(third) / sizeof(third[0]);

    if (arrays_are_equal(first, first_len, second, second_len)) {
        if (printf("Arrays first and second are equal\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Arrays first and second are not equal\n") < 0) {
            return 1;
        }
    }

    if (arrays_are_equal(first, first_len, third, third_len)) {
        if (printf("Arrays first and third are equal\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Arrays first and third are not equal\n") < 0) {
            return 1;
        }
    }

    return 0;
}