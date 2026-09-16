#include <stdio.h>
#include <stdlib.h>

int *get_first_elements(int **lists, const int *lengths, int num_lists)
{
    if (lists == NULL || lengths == NULL || num_lists <= 0) {
        return NULL;
    }

    int *result = malloc((size_t)num_lists * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < num_lists; ++i) {
        if (lists[i] == NULL || lengths[i] <= 0) {
            free(result);
            return NULL;
        }
        result[i] = lists[i][0];
    }

    return result;
}

int main(void)
{
    int list0[] = {10, 20, 30};
    int list1[] = {40, 50};
    int list2[] = {60};
    int *lists[] = {list0, list1, list2};
    /* Possible weaknesses found:
     *  Variable 'lengths' can be declared as const array [constVariable]
     */
    int lengths[] = {3, 2, 1};
    int num_lists = 3;

    int *first_elements = get_first_elements(lists, lengths, num_lists);
    if (first_elements == NULL) {
        return 1;
    }

    for (int i = 0; i < num_lists; ++i) {
        printf("%d\n", first_elements[i]);
    }

    free(first_elements);
    return 0;
}