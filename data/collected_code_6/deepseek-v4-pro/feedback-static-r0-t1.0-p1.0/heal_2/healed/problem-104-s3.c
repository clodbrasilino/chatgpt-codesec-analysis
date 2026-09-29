#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    return strcmp(str_a, str_b);
}

void sort_sublists(char ***list, int list_size, const int *sublist_sizes) {
    if (list == NULL || sublist_sizes == NULL) {
        return;
    }
    
    for (int i = 0; i < list_size; i++) {
        if (list[i] != NULL && sublist_sizes[i] > 0) {
            qsort(list[i], sublist_sizes[i], sizeof(char *), compare_strings);
        }
    }
}

int main(void) {
    char *sublist0[] = {"banana", "apple", "cherry"};
    char *sublist1[] = {"dog", "cat", "bird", "fish"};
    char *sublist2[] = {"grape"};
    
    int list_size = 3;
    const int sublist_sizes[] = {3, 4, 1};
    
    char **list[] = {sublist0, sublist1, sublist2};
    char ***list_ptr = list;
    
    sort_sublists(list_ptr, list_size, sublist_sizes);
    
    for (int i = 0; i < list_size; i++) {
        for (int j = 0; j < sublist_sizes[i]; j++) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}