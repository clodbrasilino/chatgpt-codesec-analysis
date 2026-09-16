#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool are_elements_unique(const int *list, size_t size)
{
    size_t i;
    size_t j;

    if (list == NULL) {
        return false;
    }

    for (i = 0U; i < size; i++) {
        for (j = i + 1U; j < size; j++) {
            if (list[i] == list[j]) {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    int unique_list[] = {1, 2, 3, 4, 5};
    int duplicate_list[] = {1, 2, 3, 2, 5};
    size_t unique_size = sizeof(unique_list) / sizeof(unique_list[0]);
    size_t duplicate_size = sizeof(duplicate_list) / sizeof(duplicate_list[0]);

    if (are_elements_unique(unique_list, unique_size)) {
        if (printf("List 1: all elements are unique\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("List 1: duplicate elements found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (are_elements_unique(duplicate_list, duplicate_size)) {
        if (printf("List 2: all elements are unique\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("List 2: duplicate elements found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}