#include <stdio.h>
#include <stdlib.h>

void print_duplicates(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return;
    }
    
    int *count = (int *)calloc(size, sizeof(int));
    if (count == NULL) {
        return;
    }
    
    for (int i = 0; i < size; i++) {
        if (arr[i] >= 0 && arr[i] < size) {
            count[arr[i]]++;
        }
    }
    
    int printed = 0;
    for (int i = 0; i < size; i++) {
        if (count[i] > 1) {
            if (printed) {
                printf(" ");
            }
            printf("%d", i);
            printed = 1;
        }
    }
    
    free(count);
}

int main(void) {
    int arr[] = {2, 3, 1, 2, 3, 5, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    print_duplicates(arr, size);
    printf("\n");
    
    return 0;
}