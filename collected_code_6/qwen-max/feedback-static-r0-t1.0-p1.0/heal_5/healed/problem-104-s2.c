#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char * const *)a, *(const char * const *)b);
}

void sort_sublists(char * const * const list[], const int *sizes, int num_sublists) {
    for (int i = 0; i < num_sublists; i++) {
        if (sizes[i] > 1) {
            qsort(list[i], sizes[i], sizeof(char *), compare_strings);
        }
    }
}

int main() {
    int num_sublists = 3;
    const int sizes[] = {3, 2, 4};

    char *list0[] = {"banana", "apple", "cherry"};
    char *list1[] = {"dog", "cat"};
    char *list2[] = {"zebra", "tiger", "lion", "antelope"};

    char * const *lists[] = {list0, list1, list2};

    sort_sublists(lists, sizes, num_sublists);

    for (int i = 0; i < num_sublists; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            printf("%s ", lists[i][j]);
        }
        printf("\n");
    }

    return 0;
}