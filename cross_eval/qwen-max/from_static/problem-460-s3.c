#include <stdio.h>
#include <stdlib.h>

int* get_first_elements(int** list, int size) {
    int *result = malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        result[i] = list[i][0];
    }
    return result;
}

int main() {
    int size = 3;
    int **list = (int*[]) {
        (int[]){1, 2, 3},
        (int[]){4, 5},
        (int[]){6, 7, 8, 9}
    };

    int *first_elements = get_first_elements(list, size);
    if (first_elements != NULL) {
        for (int i = 0; i < size; i++) {
            printf("%d ", first_elements[i]);
        }
        free(first_elements);
    }
    return 0;
}