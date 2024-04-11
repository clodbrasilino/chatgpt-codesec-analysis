#include <stdio.h>
#include <stdlib.h>

void find_min_indices(int *arr, int size) {
    int min = arr[0];
    int *indices = malloc(size * sizeof(int));
    int count = 0;

    for(int i = 0; i < size; i++) {
        if(arr[i] < min) {
            min = arr[i];
            count = 0;
            indices[count] = i;
        } else if(arr[i] == min) {
            indices[count] = i;
            count++;
        }
    }

    printf("Minimum value is at indices: ");
    for(int i = 0; i < count; i++) {
        printf("%d ", indices[i]);
    }
    printf("\n");

    free(indices);
}

int main() {
    int arr[] = {1, 2, 3, 1, 4, 1, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    find_min_indices(arr, size);

    return 0;
}