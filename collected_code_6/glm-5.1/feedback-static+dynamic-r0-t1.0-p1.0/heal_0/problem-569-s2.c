#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void sort_sublists(char ***lists, int *sizes, int num_lists) {
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && sizes[i] > 0) {
            qsort(lists[i], sizes[i], sizeof(char *), compare_strings);
        }
    }
}

void free_lists(char ***lists, int *sizes, int num_lists) {
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL) {
            for (int j = 0; j < sizes[i]; j++) {
                free(lists[i][j]);
            }
            free(lists[i]);
        }
    }
    free(lists);
    free(sizes);
}

int main(void) {
    int num_lists = 3;
    char ***lists = malloc(num_lists * sizeof(char **));
    if (lists == NULL) return 1;
    
    int *sizes = malloc(num_lists * sizeof(int));
    if (sizes == NULL) {
        free(lists);
        return 1;
    }

    sizes[0] = 3;
    lists[0] = malloc(sizes[0] * sizeof(char *));
    if (lists[0] == NULL) {
        free(sizes);
        free(lists);
        return 1;
    }
    lists[0][0] = strdup("banana");
    lists[0][1] = strdup("apple");
    lists[0][2] = strdup("cherry");
    if (lists[0][0] == NULL || lists[0][1] == NULL || lists[0][2] == NULL) {
        for(int i = 0; i < sizes[0]; i++) free(lists[0][i]);
        free(lists[0]);
        free(sizes);
        free(lists);
        return 1;
    }

    sizes[1] = 2;
    lists[1] = malloc(sizes[1] * sizeof(char *));
    if (lists[1] == NULL) {
        for(int i = 0; i < sizes[0]; i++) free(lists[0][i]);
        free(lists[0]);
        free(sizes);
        free(lists);
        return 1;
    }
    lists[1][0] = strdup("zebra");
    lists[1][1] = strdup("ant");
    if (lists[1][0] == NULL || lists[1][1] == NULL) {
        for(int i = 0; i < sizes[0]; i++) free(lists[0][i]);
        free(lists[0]);
        for(int i = 0; i < sizes[1]; i++) if(lists[1][i]) free(lists[1][i]);
        free(lists[1]);
        free(sizes);
        free(lists);
        return 1;
    }

    sizes[2] = 0;
    lists[2] = NULL;

    sort_sublists(lists, sizes, num_lists);

    for (int i = 0; i < num_lists; i++) {
        printf("List %d:\n", i);
        for (int j = 0; j < sizes[i]; j++) {
            printf("  %s\n", lists[i][j]);
        }
    }

    free_lists(lists, sizes, num_lists);
    
    return 0;
}