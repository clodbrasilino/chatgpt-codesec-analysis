#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    const char *const *str_a = (const char *const *)a;
    const char *const *str_b = (const char *const *)b;
    return strcmp(*str_a, *str_b);
}

void sort_sublists(char ***list, int list_size, const int *sublist_sizes) {
    for (int i = 0; i < list_size; ++i) {
        if (sublist_sizes[i] > 0 && list[i] != NULL) {
            qsort(list[i], sublist_sizes[i], sizeof(char *), compare_strings);
        }
    }
}

int main(void) {
    char *sublist1[] = {"banana", "apple", "cherry"};
    char *sublist2[] = {"delta", "charlie", "bravo", "alpha"};
    char *sublist3[] = {"zebra", "yankee"};

    char **list[] = {sublist1, sublist2, sublist3};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    int sizes[] = {3, 4, 2};
    int list_size = 3;

    sort_sublists(list, list_size, sizes);

    for (int i = 0; i < list_size; ++i) {
        printf("Sublist %d: ", i);
        for (int j = 0; j < sizes[i]; ++j) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }

    return 0;
}