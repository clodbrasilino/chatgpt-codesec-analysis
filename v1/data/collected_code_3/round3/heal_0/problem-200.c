#include <stdio.h>
#include <stdlib.h>

void findMaxIndexes(int* arr, int len) {
    int max = arr[0];
    int* indexes = (int*)malloc(len * sizeof(int));
    int count = 0;

    for (int i = 0; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
            count = 0;
            indexes[count++] = i;
        } else if (arr[i] == max) {
            indexes[count++] = i;
        }
    }

    printf("Max value is %d at indexes: ", max);
    for (int i = 0; i < count; i++) {
        printf("%d ", indexes[i]);
    }
    printf("\n");

    free(indexes);
}

int main() {
    int arr[] = {1, 3, 5, 7, 7, 5, 3, 1};
    int len = sizeof(arr) / sizeof(arr[0]);

    findMaxIndexes(arr, len);

    return 0;
}