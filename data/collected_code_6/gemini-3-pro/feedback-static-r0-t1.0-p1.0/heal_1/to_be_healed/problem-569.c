#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_string_array(char **array, int size) {
    if (!array) return;
    for (int i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}

void free_list_of_lists(char ***list, int *sizes, int num_lists) {
    if (!list || !sizes) return;
    for (int i = 0; i < num_lists; i++) {
        free_string_array(list[i], sizes[i]);
    }
    free(list);
    free(sizes);
}

int compare_strings(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    return strcmp(str_a, str_b);
}

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
void sort_sublists(char ***list, int *sizes, int num_lists) {
    if (!list || !sizes || num_lists <= 0) return;
    for (int i = 0; i < num_lists; i++) {
        if (list[i] && sizes[i] > 0) {
            qsort(list[i], sizes[i], sizeof(char *), compare_strings);
        }
    }
}

int main(void) {
    int num_lists = 2;
    int *sizes = malloc(num_lists * sizeof(int));
    if (!sizes) return EXIT_FAILURE;

    char ***list = malloc(num_lists * sizeof(char **));
    if (!list) {
        free(sizes);
        return EXIT_FAILURE;
    }

    sizes[0] = 3;
    list[0] = malloc(sizes[0] * sizeof(char *));
    if (!list[0]) {
        free(list);
        free(sizes);
        return EXIT_FAILURE;
    }
    list[0][0] = strdup("banana");
    list[0][1] = strdup("apple");
    list[0][2] = strdup("cherry");
    if (!list[0][0] || !list[0][1] || !list[0][2]) {
        free_list_of_lists(list, sizes, 1);
        return EXIT_FAILURE;
    }

    sizes[1] = 2;
    list[1] = malloc(sizes[1] * sizeof(char *));
    if (!list[1]) {
        free_list_of_lists(list, sizes, 2);
        return EXIT_FAILURE;
    }
    list[1][0] = strdup("zebra");
    list[1][1] = strdup("monkey");
    if (!list[1][0] || !list[1][1]) {
        free_list_of_lists(list, sizes, 2);
        return EXIT_FAILURE;
    }

    sort_sublists(list, sizes, num_lists);

    for (int i = 0; i < num_lists; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }

    free_list_of_lists(list, sizes, num_lists);

    return EXIT_SUCCESS;
}