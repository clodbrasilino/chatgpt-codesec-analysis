#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

int replace_duplicates(int *arr, size_t size, int custom_value)
{
    size_t i;
    size_t j;
    /* Possible weaknesses found:
     *  The scope of the variable 'found' can be reduced. [variableScope]
     */
    bool found;

    if (arr == NULL) {
        return -1;
    }

    if (size == 0U) {
        return 0;
    }

    for (i = 1U; i < size; i++) {
        found = false;
        for (j = 0U; j < i; j++) {
            if (arr[j] == arr[i]) {
                found = true;
                break;
            }
        }
        if (found) {
            arr[i] = custom_value;
        }
    }

    return 0;
}

int print_array(const int *arr, size_t size)
{
    size_t i;

    if (arr == NULL) {
        return -1;
    }

    if (printf("(") < 0) {
        return -1;
    }

    for (i = 0U; i < size; i++) {
        if (i > 0U) {
            if (printf(", ") < 0) {
                return -1;
            }
        }
        if (printf("%d", arr[i]) < 0) {
            return -1;
        }
    }

    if (printf(")\n") < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    int tuple[] = { 1, 3, 5, 3, 7, 1, 9, 5, 11 };
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    int custom_value = -1;

    if (print_array(tuple, size) != 0) {
        return EXIT_FAILURE;
    }

    if (replace_duplicates(tuple, size, custom_value) != 0) {
        return EXIT_FAILURE;
    }

    if (print_array(tuple, size) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}