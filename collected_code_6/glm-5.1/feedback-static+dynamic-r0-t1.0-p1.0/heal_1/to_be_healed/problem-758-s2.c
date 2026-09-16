#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void *a, const void *b) {
    return (*(const int *)a > *(const int *)b) - (*(const int *)a < *(const int *)b);
}

size_t count_unique_lists(int **lists, const size_t *lengths, size_t num_lists) {
    if (num_lists == 0) {
        return 0;
    }

    char *seen = calloc(num_lists, sizeof(char));
    if (seen == NULL) {
        return 0;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < num_lists; i++) {
        if (seen[i] == 1) {
            continue;
        }

        seen[i] = 1;
        unique_count++;

        for (size_t j = i + 1; j < num_lists; j++) {
            if (seen[j] == 1) {
                continue;
            }

            if (lengths[i] != lengths[j]) {
                continue;
            }

            int match = 1;
            int *list_i_copy = NULL;
            int *list_j_copy = NULL;

            if (lengths[i] > 0) {
                list_i_copy = malloc(lengths[i] * sizeof(int));
                list_j_copy = malloc(lengths[j] * sizeof(int));

                if (list_i_copy == NULL || list_j_copy == NULL) {
                    free(list_i_copy);
                    free(list_j_copy);
                    free(seen);
                    return 0;
                }

                memcpy(list_i_copy, lists[i], lengths[i] * sizeof(int));
                memcpy(list_j_copy, lists[j], lengths[j] * sizeof(int));

                qsort(list_i_copy, lengths[i], sizeof(int), compare_ints);
                qsort(list_j_copy, lengths[j], sizeof(int), compare_ints);

                match = (memcmp(list_i_copy, list_j_copy, lengths[i] * sizeof(int)) == 0) ? 1 : 0;

                free(list_i_copy);
                free(list_j_copy);
            }

            if (match == 1) {
                seen[j] = 1;
            }
        }
    }

    free(seen);
    return unique_count;
}

int main(void) {
    int list1[] = {1, 2, 3};
    int list2[] = {3, 2, 1};
    int list3[] = {4, 5};
    int list4[] = {5, 4};
    int list5[] = {1, 2, 3, 4};
    int list6[] = {1, 2, 3};

    int *lists[] = {list1, list2, list3, list4, list5, list6};
    /* Possible weaknesses found:
     *  Variable 'lengths' can be declared as const array [constVariable]
     */
    size_t lengths[] = {3, 3, 2, 2, 4, 3};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    size_t unique = count_unique_lists(lists, lengths, num_lists);

    printf("%zu\n", unique);

    return 0;
}