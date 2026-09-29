#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    return strcmp(str_a, str_b);
}

void sort_sublists(char ***list_of_lists, const int *sublist_sizes, int num_sublists) {
    if (list_of_lists == NULL || sublist_sizes == NULL) {
        return;
    }

    for (int i = 0; i < num_sublists; i++) {
        if (list_of_lists[i] != NULL && sublist_sizes[i] > 0) {
            qsort(list_of_lists[i], sublist_sizes[i], sizeof(char *), compare_strings);
        }
    }
}

int main(void) {
    char *sublist1[] = {"kiwi", "apple", "banana", NULL};
    char *sublist2[] = {"zebra", "monkey", "elephant", "cat", NULL};
    char *sublist3[] = {"sun", "moon", "star", NULL};

    char **list_of_lists[] = {sublist1, sublist2, sublist3};
    /* Possible weaknesses found:
     *  Variable 'sublist_sizes' can be declared as const array [constVariable]
     */
    int sublist_sizes[] = {3, 4, 3};
    int num_sublists = 3;

    sort_sublists(list_of_lists, sublist_sizes, num_sublists);

    for (int i = 0; i < num_sublists; i++) {
        for (int j = 0; j < sublist_sizes[i]; j++) {
            printf("%s ", list_of_lists[i][j]);
        }
        printf("\n");
    }

    return 0;
}