#include <stddef.h>
#include <stdio.h>

int *find_max_length_list(int **lists, size_t list_count, const size_t *lengths, size_t *max_length) {
    size_t i;
    size_t max_index;
    if (lists == NULL || lengths == NULL || list_count == 0) {
        if (max_length != NULL) {
            *max_length = 0;
        }
        return NULL;
    }
    for (i = 0; i < list_count; i++) {
        if (lengths[i] > 0 && lists[i] == NULL) {
            if (max_length != NULL) {
                *max_length = 0;
            }
            return NULL;
        }
    }
    max_index = 0;
    for (i = 1; i < list_count; i++) {
        if (lengths[i] > lengths[max_index]) {
            max_index = i;
        }
    }
    if (max_length != NULL) {
        *max_length = lengths[max_index];
    }
    return lists[max_index];
}

int main(void) {
    int list0[] = {1, 2, 3};
    int list1[] = {4, 5};
    int list2[] = {6, 7, 8, 9};
    int *lists[] = {list0, list1, list2};
    /* Possible weaknesses found:
     *  Variable 'lengths' can be declared as const array [constVariable]
     */
    size_t lengths[] = {3, 2, 4};
    size_t max_length = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    /* Possible weaknesses found:
     *  Variable 'max_list' can be declared as pointer to const [constVariablePointer]
     */
    int *max_list = find_max_length_list(lists, 3, lengths, &max_length);
    if (max_list != NULL) {
        for (i = 0; i < max_length; i++) {
            printf("%d ", max_list[i]);
        }
        printf("\n");
    } else {
        printf("No list found\n");
    }
    return 0;
}