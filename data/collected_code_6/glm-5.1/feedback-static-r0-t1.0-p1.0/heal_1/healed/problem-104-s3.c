#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void sort_sublists(char ***lists, int num_lists, const int *sublist_sizes) {
    if (lists == NULL || sublist_sizes == NULL) {
        return;
    }
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && sublist_sizes[i] > 0) {
            qsort(lists[i], sublist_sizes[i], sizeof(char *), compare_strings);
        }
    }
}

void free_lists(char ***lists, int num_lists, const int *sublist_sizes) {
    if (lists == NULL) {
        return;
    }
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL) {
            for (int j = 0; j < sublist_sizes[i]; j++) {
                free(lists[i][j]);
            }
            free(lists[i]);
        }
    }
    free(lists);
}

int main(void) {
    int num_lists = 3;
    const int sublist_sizes[] = {3, 2, 4};
    
    char ***lists = malloc(num_lists * sizeof(char **));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    lists[0] = malloc(sublist_sizes[0] * sizeof(char *));
    if (lists[0] == NULL) { free(lists); return EXIT_FAILURE; }
    lists[0][0] = strdup("banana");
    lists[0][1] = strdup("apple");
    lists[0][2] = strdup("cherry");
    if (!lists[0][0] || !lists[0][1] || !lists[0][2]) { free_lists(lists, 1, sublist_sizes); return EXIT_FAILURE; }

    lists[1] = malloc(sublist_sizes[1] * sizeof(char *));
    if (lists[1] == NULL) { free_lists(lists, 1, sublist_sizes); return EXIT_FAILURE; }
    lists[1][0] = strdup("zebra");
    lists[1][1] = strdup("ant");
    if (!lists[1][0] || !lists[1][1]) { free_lists(lists, 2, sublist_sizes); return EXIT_FAILURE; }

    lists[2] = malloc(sublist_sizes[2] * sizeof(char *));
    if (lists[2] == NULL) { free_lists(lists, 2, sublist_sizes); return EXIT_FAILURE; }
    lists[2][0] = strdup("dog");
    lists[2][1] = strdup("cat");
    lists[2][2] = strdup("elephant");
    lists[2][3] = strdup("bird");
    if (!lists[2][0] || !lists[2][1] || !lists[2][2] || !lists[2][3]) { free_lists(lists, 3, sublist_sizes); return EXIT_FAILURE; }

    sort_sublists(lists, num_lists, sublist_sizes);

    for (int i = 0; i < num_lists; i++) {
        for (int j = 0; j < sublist_sizes[i]; j++) {
            printf("%s ", lists[i][j]);
        }
        printf("\n");
    }

    free_lists(lists, num_lists, sublist_sizes);

    return EXIT_SUCCESS;
}