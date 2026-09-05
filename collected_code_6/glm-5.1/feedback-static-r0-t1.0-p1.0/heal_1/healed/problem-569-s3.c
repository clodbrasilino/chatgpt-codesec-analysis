#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void sort_sublists(char ***lists, const size_t *list_sizes, size_t num_lists) {
    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && list_sizes[i] > 0) {
            qsort(lists[i], list_sizes[i], sizeof(char *), compare_strings);
        }
    }
}

int main(void) {
    char *sublist1[] = {"zebra", "apple", "mango"};
    char *sublist2[] = {"lion", "tiger", "bear", "elephant"};
    char *sublist3[] = {"ocean"};
    
    const size_t sizes[] = {3, 4, 1};
    size_t num_lists = 3;

    char **lists[] = {sublist1, sublist2, sublist3};

    sort_sublists(lists, sizes, num_lists);

    for (size_t i = 0; i < num_lists; i++) {
        for (size_t j = 0; j < sizes[i]; j++) {
            printf("%s ", lists[i][j]);
        }
        printf("\n");
    }

    return 0;
}