#include <stdio.h>
#include <stdlib.h>

void find_cubes(int *list, int size, int *result) {
    for (int i = 0; i < size; ++i) {
        result[i] = list[i] * list[i] * list[i];
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    int *result = (int *)malloc(size * sizeof(int));
    
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    find_cubes(list, size, result);

    for (int i = 0; i < size; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}