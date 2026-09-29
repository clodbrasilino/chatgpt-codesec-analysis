#include <stdio.h>
#include <stdlib.h>

int count_pairs_with_sum(const int *arr, size_t size, int sum) {
    if (arr == NULL) {
        return 0;
    }
    
    int count = 0;
    
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] + arr[j] == sum) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    int arr[] = {1, 5, 7, -1, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int sum = 6;
    
    int result = count_pairs_with_sum(arr, size, sum);
    
    printf("Count of pairs with sum %d: %d\n", sum, result);
    
    return 0;
}