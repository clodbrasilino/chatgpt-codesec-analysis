#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    if (str_a == NULL || str_b == NULL) {
        return 0;
    }
    return strcmp(str_a, str_b);
}

int sort_sublists(char ***list, size_t list_size, const size_t *sublist_sizes) {
    size_t i;
    
    if (list == NULL || sublist_sizes == NULL) {
        return -1;
    }
    
    for (i = 0; i < list_size; i++) {
        if (list[i] != NULL && sublist_sizes[i] > 0) {
            qsort(list[i], sublist_sizes[i], sizeof(char *), compare_strings);
        }
    }
    
    return 0;
}

int main(void) {
    char *sublist1[] = {"banana", "apple", "cherry"};
    char *sublist2[] = {"zebra", "elephant", "ant", "dog"};
    char *sublist3[] = {"grape", "orange"};
    
    char **list[] = {sublist1, sublist2, sublist3};
    const size_t sublist_sizes[] = {3, 4, 2};
    size_t list_size = 3;
    
    size_t i, j;
    int result;
    
    result = sort_sublists(list, list_size, sublist_sizes);
    if (result != 0) {
        fprintf(stderr, "Error: Failed to sort sublists\n");
        return EXIT_FAILURE;
    }
    
    for (i = 0; i < list_size; i++) {
        printf("Sublist %zu: ", i);
        for (j = 0; j < sublist_sizes[i]; j++) {
            if (list[i][j] != NULL) {
                printf("%s ", list[i][j]);
            }
        }
        printf("\n");
    }
    
    return EXIT_SUCCESS;
}