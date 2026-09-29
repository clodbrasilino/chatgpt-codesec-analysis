#include <stdio.h>
#include <stdlib.h>

void remove_negatives(int **list, int *size) {
    int *new_list = (int *)malloc(*size * sizeof(int));
    if (new_list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    int j = 0;
    for (int i = 0; i < *size; i++) {
        if ((*list)[i] >= 0) {
            new_list[j++] = (*list)[i];
        }
    }
    free(*list);
    *list = new_list;
    *size = j;
}

int main() {
    int size = 5;
    int *list = (int *)malloc(size * sizeof(int));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    list[0] = -1;
    list[1] = 2;
    list[2] = -3;
    list[3] = 4;
    list[4] = -5;

    remove_negatives(&list, &size);

    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return 0;
}