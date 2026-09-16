#include <stdio.h>
#include <stdlib.h>

void print_duplicates(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return;
    }
    
    int min = arr[0], max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    
    int range = max - min + 1;
    int *count = (int *)calloc(range, sizeof(int));
    if (count == NULL) {
        return;
    }
    
    for (int i = 0; i < size; i++) {
        count[arr[i] - min]++;
    }
    
    for (int i = 0; i < range; i++) {
        if (count[i] > 1) {
            printf("%d ", i + min);
        }
    }
    printf("\n");
    
    free(count);
}

int main(void) {
    int numbers[] = {4, 2, 4, 5, 2, 3, 1, 5, 4};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    print_duplicates(numbers, size);
    
    return 0;
}