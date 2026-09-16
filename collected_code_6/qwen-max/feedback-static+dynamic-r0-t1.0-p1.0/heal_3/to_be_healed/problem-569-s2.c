#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void sort_sublists(char *list[][10], int num_lists, const int sublist_sizes[]) {
    for (int i = 0; i < num_lists; ++i) {
        qsort(list[i], sublist_sizes[i], sizeof(char *), compare);
    }
}

int main() {
    char *list1[] = {"banana", "apple", "cherry"};
    char *list2[] = {"dog", "cat", "elephant", "bird"};
    char *list3[] = {"red", "blue", "green", "yellow"};

    /* Possible weaknesses found:
     *  (near initialization for 'list[0][1]')
     *  (near initialization for 'list[0][2]')
     *  initialization of 'char *' from incompatible pointer type 'char **' [-Wincompatible-pointer-types]
     *  (near initialization for 'list[0][0]')
     */
    char *list[3][10] = {list1, list2, list3};
    const int sublist_sizes[] = {3, 4, 4};
    int num_lists = 3;

    sort_sublists(list, num_lists, sublist_sizes);

    for (int i = 0; i < num_lists; ++i) {
        for (int j = 0; j < sublist_sizes[i]; ++j) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }

    return 0;
}