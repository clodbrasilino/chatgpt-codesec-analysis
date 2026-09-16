#include <stdio.h>
#include <stdlib.h>

size_t count_sublists_with_element(const int *const *sublists,
                                   const size_t *lengths,
                                   size_t num_sublists,
                                   int target)
{
    size_t count = 0;
    size_t i;
    size_t j;

    if (sublists == NULL || lengths == NULL) {
        return 0;
    }

    for (i = 0; i < num_sublists; i++) {
        if (sublists[i] == NULL) {
            continue;
        }
        for (j = 0; j < lengths[i]; j++) {
            if (sublists[i][j] == target) {
                count++;
                break;
            }
        }
    }

    return count;
}

int main(void)
{
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 1};
    int list3[] = {6, 7, 8};
    int list4[] = {1, 1, 9};

    const int *sublists[] = {list1, list2, list3, list4};
    const size_t lengths[] = {3, 3, 3, 3};
    size_t num_sublists = sizeof(sublists) / sizeof(sublists[0]);

    int target = 1;
    size_t result = count_sublists_with_element(sublists, lengths, num_sublists, target);

    if (printf("Number of sublists containing %d: %zu\n", target, result) < 0) {
        return EXIT_FAILURE;
    }

    target = 6;
    result = count_sublists_with_element(sublists, lengths, num_sublists, target);

    if (printf("Number of sublists containing %d: %zu\n", target, result) < 0) {
        return EXIT_FAILURE;
    }

    target = 100;
    result = count_sublists_with_element(sublists, lengths, num_sublists, target);

    if (printf("Number of sublists containing %d: %zu\n", target, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}