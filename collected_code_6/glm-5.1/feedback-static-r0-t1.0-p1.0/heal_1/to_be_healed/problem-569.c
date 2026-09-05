#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
void sort_sublists(char ***lists, int *sizes, int num_lists) {
    if (lists == NULL || sizes == NULL) return;
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && sizes[i] > 0) {
            qsort(lists[i], (size_t)sizes[i], sizeof(char *), compare_strings);
        }
    }
}

void free_lists(char ***lists, int *sizes, int num_lists) {
    if (lists == NULL) return;
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
    int num_lists = 2;
    int *sizes = malloc((size_t)num_lists * sizeof(int));
    if (sizes == NULL) return EXIT_FAILURE;

    char ***lists = malloc((size_t)num_lists * sizeof(char **));
    if (lists == NULL) {
        free(sizes);
        return EXIT_FAILURE;
    }

    sizes[0] = 3;
    lists[0] = malloc((size_t)sizes[0] * sizeof(char *));
    if (lists[0] == NULL) {
        free(lists);
        free(sizes);
        return EXIT_FAILURE;
    }
    lists[0][0] = strdup("banana");
    lists[0][1] = strdup("apple");
    lists[0][2] = strdup("cherry");
    if (lists[0][0] == NULL || lists[0][1] == NULL || lists[0][2] == NULL) {
        free_lists(lists, sizes, num_lists);
        return EXIT_FAILURE;
    }

    sizes[1] = 2;
    lists[1] = malloc((size_t)sizes[1] * sizeof(char *));
    if (lists[1] == NULL) {
        free_lists(lists, sizes, num_lists);
        return EXIT_FAILURE;
    }
    lists[1][0] = strdup("zebra");
    lists[1][1] = strdup("antelope");
    if (lists[1][0] == NULL || lists[1][1] == NULL) {
        free_lists(lists, sizes, num_lists);
        return EXIT_FAILURE;
    }

    sort_sublists(lists, sizes, num_lists);

    for (int i = 0; i < num_lists; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            printf("%s ", lists[i][j]);
        }
        printf("\n");
    }

    free_lists(lists, sizes, num_lists);

    return EXIT_SUCCESS;
}