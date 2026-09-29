#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

/* Possible weaknesses found:
 *  Parameter 'sublist_sizes' can be declared as const array [constParameter]
 *  array type has incomplete element type 'char *[]'
 *  declaration of 'list' as multidimensional array must have bounds for all dimensions except the first
 *  array has incomplete element type 'char *[]'
 */
void sort_sublists(char *list[][], int num_lists, int sublist_sizes[]) {
    for (int i = 0; i < num_lists; ++i) {
        qsort(list[i], sublist_sizes[i], sizeof(char *), compare);
    }
}

int main() {
    char *list1[] = {"banana", "apple", "cherry"};
    char *list2[] = {"dog", "cat", "elephant", "bird"};
    char *list3[] = {"red", "blue", "green", "yellow"};

    /* Possible weaknesses found:
     *  array type has incomplete element type 'char *[]'
     *  declaration of 'list' as multidimensional array must have bounds for all dimensions except the first
     *  array has incomplete element type 'char *[]'
     */
    char *list[][] = {list1, list2, list3};
    int sublist_sizes[] = {3, 4, 4};
    int num_lists = 3;

    /* Possible weaknesses found:
     *  type of formal parameter 1 is incomplete
     */
    sort_sublists(list, num_lists, sublist_sizes);

    for (int i = 0; i < num_lists; ++i) {
        for (int j = 0; j < sublist_sizes[i]; ++j) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }

    return 0;
}