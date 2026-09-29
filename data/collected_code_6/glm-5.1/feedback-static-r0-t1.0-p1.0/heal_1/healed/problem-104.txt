#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void sort_sublists(char ***lists, const int *sizes, int count) {
    if (lists == NULL || sizes == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        if (lists[i] != NULL && sizes[i] > 0) {
            qsort(lists[i], sizes[i], sizeof(char *), compare_strings);
        }
    }
}

void free_lists(char ***lists, int *sizes, int count) {
    if (lists == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
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
    int count = 3;
    int *sizes = malloc(count * sizeof(int));
    if (sizes == NULL) {
        return EXIT_FAILURE;
    }
    sizes[0] = 3;
    sizes[1] = 2;
    sizes[2] = 4;

    char ***lists = malloc(count * sizeof(char **));
    if (lists == NULL) {
        free(sizes);
        return EXIT_FAILURE;
    }

    lists[0] = malloc(sizes[0] * sizeof(char *));
    if (lists[0] == NULL) {
        free(lists);
        free(sizes);
        return EXIT_FAILURE;
    }
    lists[0][0] = strdup("banana");
    lists[0][1] = strdup("apple");
    lists[0][2] = strdup("cherry");
    if (lists[0][0] == NULL || lists[0][1] == NULL || lists[0][2] == NULL) {
        free_lists(lists, sizes, 1);
        return EXIT_FAILURE;
    }

    lists[1] = malloc(sizes[1] * sizeof(char *));
    if (lists[1] == NULL) {
        free_lists(lists, sizes, 1);
        return EXIT_FAILURE;
    }
    lists[1][0] = strdup("zebra");
    lists[1][1] = strdup("elephant");
    if (lists[1][0] == NULL || lists[1][1] == NULL) {
        free_lists(lists, sizes, 2);
        return EXIT_FAILURE;
    }

    lists[2] = malloc(sizes[2] * sizeof(char *));
    if (lists[2] == NULL) {
        free_lists(lists, sizes, 2);
        return EXIT_FAILURE;
    }
    lists[2][0] = strdup("delta");
    lists[2][1] = strdup("alpha");
    lists[2][2] = strdup("charlie");
    lists[2][3] = strdup("bravo");
    if (lists[2][0] == NULL || lists[2][1] == NULL || lists[2][2] == NULL || lists[2][3] == NULL) {
        free_lists(lists, sizes, 3);
        return EXIT_FAILURE;
    }

    sort_sublists(lists, sizes, count);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            printf("%s ", lists[i][j]);
        }
        printf("\n");
    }

    free_lists(lists, sizes, count);

    return EXIT_SUCCESS;
}