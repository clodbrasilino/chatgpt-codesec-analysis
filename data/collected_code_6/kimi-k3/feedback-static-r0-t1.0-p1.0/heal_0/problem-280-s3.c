#include <stdio.h>

int sequential_search(const int *arr, size_t size, int target) {
    size_t i;
    if (arr == NULL) {
        return -1;
    }
    for (i = 0; i < size; i++) {
        if (arr[i] == target) {
            return (int)i;
        }
    }
    return -1;
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target;
    int result;
    
    printf("Enter element to search: ");
    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    result = sequential_search(arr, size, target);
    
    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }
    
    return 0;
}