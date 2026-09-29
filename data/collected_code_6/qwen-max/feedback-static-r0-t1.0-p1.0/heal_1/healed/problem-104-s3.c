#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char *const *)a, *(const char *const *)b);
}

void sort_sublists(char ***list, const int *sublist_sizes, int list_size) {
    for (int i = 0; i < list_size; i++) {
        qsort(list[i], sublist_sizes[i], sizeof(char *), compare_strings);
    }
}

int main() {
    char *list1[] = {"apple", "banana", "cherry"};
    char *list2[] = {"dog", "cat", "elephant"};
    char *list3[] = {"zebra", "giraffe", "lion"};

    const int sublist_sizes[] = {3, 3, 3};
    int list_size = 3;

    char ***main_list = malloc(list_size * sizeof(char **));
    if (main_list == NULL) {
        return 1;
    }

    for (int i = 0; i < list_size; i++) {
        main_list[i] = (i == 0) ? list1 : (i == 1) ? list2 : list3;
    }

    sort_sublists(main_list, sublist_sizes, list_size);

    for (int i = 0; i < list_size; i++) {
        for (int j = 0; j < sublist_sizes[i]; j++) {
            printf("%s ", main_list[i][j]);
        }
        printf("\n");
    }

    free(main_list);
    return 0;
}