#include <stdio.h>
#include <stdlib.h>

void find_min_indices(const int *list, int list_size, int **indices, int *indices_size) {
    if (list == NULL || list_size <= 0) return;
    
    *indices = (int *)malloc(list_size * sizeof(int));
    if (*indices == NULL) return;
    
    int min_value = list[0];
    for (int i = 1; i < list_size; i++) {
        if (list[i] < min_value) {
            min_value = list[i];
        }
    }
    
    *indices_size = 0;
    for (int i = 0; i < list_size; i++) {
        if (list[i] == min_value) {
            (*indices)[(*indices_size)++] = i;
        }
    }
}

int main() {
    int list[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int list_size = sizeof(list) / sizeof(list[0]);
    int *indices = NULL;
    int indices_size = 0;
    
    find_min_indices(list, list_size, &indices, &indices_size);
    
    for (int i = 0; i < indices_size; i++) {
        printf("Index: %d\n", indices[i]);
    }
    
    free(indices);
    
    return 0;
}