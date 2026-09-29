#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIST_SIZE 100

typedef int List[MAX_LIST_SIZE];

int are_identical_lists(const List *list1, const List *list2, int n) {
    for (int i = 0; i < n; ++i) {
        if (list1[i] != list2[i]) {
            return 0;
        }
    }
    return 1;
}

int count_unique_lists(List lists[], int size, int n) {
    int unique_count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'is_unique' can be reduced. [variableScope]
     */
    int is_unique;

    for (int i = 0; i < size; ++i) {
        is_unique = 1;
        for (int j = 0; j < i; ++j) {
            if (are_identical_lists(lists + i, lists + j, n)) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            ++unique_count;
        }
    }
    return unique_count;
}

int main() {
    List lists[] = {
        {1, 2, 3},
        {4, 5, 6},
        {1, 2, 3},
        {7, 8, 9},
        {4, 5, 6}
    };
    int num_elements_in_list = 3;
    int num_lists = sizeof(lists) / sizeof(List);

    int unique_count = count_unique_lists(lists, num_lists, num_elements_in_list);
    printf("Number of unique lists: %d\n", unique_count);

    return 0;
}