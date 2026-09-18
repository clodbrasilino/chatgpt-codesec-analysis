#include <stdio.h>
#include <stdlib.h>

int remove_even_numbers(int **list, size_t *size) {
    if (!list || !size || (*size > 0 && !*list)) {
        return -1;
    }

    if (*size == 0) {
        return 0;
    }

    size_t odd_count = 0;
    for (size_t i = 0; i < *size; i++) {
        if ((*list)[i] % 2 != 0) {
            odd_count++;
        }
    }

    if (odd_count == 0) {
        free(*list);
        *list = NULL;
        *size = 0;
        return 0;
    }

    if (odd_count == *size) {
        return 0;
    }

    int *new_list = malloc(odd_count * sizeof(int));
    if (!new_list) {
        return -1;
    }

    size_t index = 0;
    for (size_t i = 0; i < *size; i++) {
        if ((*list)[i] % 2 != 0) {
            new_list[index++] = (*list)[i];
        }
    }

    free(*list);
    *list = new_list;
    *size = odd_count;

    return 0;
}

int main(void) {
    size_t size = 10;
    int *list = malloc(size * sizeof(int));
    
    if (!list) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        list[i] = (int)(i + 1);
    }

    if (remove_even_numbers(&list, &size) != 0) {
        free(list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return EXIT_SUCCESS;
}