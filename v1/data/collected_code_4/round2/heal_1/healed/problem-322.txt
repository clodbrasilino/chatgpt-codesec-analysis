#include <stdio.h>
#include <stdlib.h>

void find_min_indices(int* array, int length) {
    if(length == 0 || array == NULL) {
        printf("Array is empty or NULL.\n");
        return;
    }
    
    int min = array[0];
    int *indices = (int*) malloc(length * sizeof(int));
    if (indices == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    int indices_count = 0;

    for(int i = 0; i < length; i++) {
        if(array[i] < min) {
            min = array[i];
        }
    }

    for(int i = 0; i < length; i++) {
        if(array[i] == min) {
            indices[indices_count++] = i;
        }
    }

    printf("Indices of minimum values: ");
    
    for(int i = 0; i < indices_count; i++) {
        printf("%d ", indices[i]);
    }
    printf("\n");

    free(indices);
}

int main() {
    int array[6] = {5, 7, 3, 4, 3, 2};
    find_min_indices(array, 6);
   
    return 0;
}