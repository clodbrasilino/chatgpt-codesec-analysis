#include <stdio.h>

void removeElements(const int arr[], int n, int dataType) {
    int index = 0;
    int i;
  
    for (i = 0; i < n; i++) {
        if (arr[i] != dataType) {
            arr[index++] = arr[i];
        }
    }
  
    while (index < n) {
        arr[index++] = 0;
    }
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int dataType = 4;
  
    printf("Original Tuple:\n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", tuple[i]);
    }
  
    removeElements(tuple, size, dataType);
  
    printf("\nTuple after removing %d:\n", dataType);
    for (int i = 0; i < size; i++) {
        printf("%d\n", tuple[i]);
    }
  
    return 0;
}