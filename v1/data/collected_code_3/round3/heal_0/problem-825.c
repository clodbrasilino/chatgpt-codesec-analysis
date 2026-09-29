#include <stdio.h>

void accessElements(int* arr, int* indices, int arrSize, int indicesSize) {
    for(int i = 0; i < indicesSize; i++) {
        if(indices[i] < arrSize) {
            printf("%d ", arr[indices[i]]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int indices[] = {0, 3, 5, 9};

    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int indicesSize = sizeof(indices) / sizeof(indices[0]);

    accessElements(arr, indices, arrSize, indicesSize);

    return 0;
}