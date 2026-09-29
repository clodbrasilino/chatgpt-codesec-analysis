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
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int indices[] = {1, 3, 5, 7, 9};

    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int indicesSize = sizeof(indices) / sizeof(indices[0]);

    accessElements(arr, indices, arrSize, indicesSize);

    return 0;
}