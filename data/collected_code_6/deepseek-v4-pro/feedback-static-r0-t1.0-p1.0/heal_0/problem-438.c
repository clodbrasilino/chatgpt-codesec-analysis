#include <stdio.h>
#include <stdlib.h>

int count_bidirectional_pairs(int *arr, int size) {
    int count = 0;
    int *visited = (int *)calloc(size, sizeof(int));
    
    if (visited == NULL) {
        return -1;
    }
    
    for (int i = 0; i < size; i++) {
        if (visited[i]) {
            continue;
        }
        
        for (int j = i + 1; j < size; j++) {
            if (visited[j]) {
                continue;
            }
            
            if (arr[i] == arr[j]) {
                count++;
                visited[i] = 1;
                visited[j] = 1;
                break;
            }
        }
    }
    
    int *pair_count = (int *)calloc(1001, sizeof(int));
    if (pair_count == NULL) {
        free(visited);
        return -1;
    }
    
    int bidirectional_count = 0;
    for (int i = 0; i < size; i++) {
        pair_count[arr[i]]++;
    }
    
    for (int i = 0; i < 1001; i++) {
        if (pair_count[i] >= 2) {
            bidirectional_count += pair_count[i] / 2;
        }
    }
    
    free(visited);
    free(pair_count);
    
    return bidirectional_count;
}

int main() {
    int arr1[] = {1, 2, 3, 2, 1, 3, 4, 1};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int result1 = count_bidirectional_pairs(arr1, size1);
    printf("Array 1 bidirectional pairs: %d\n", result1);
    
    int arr2[] = {1, 2, 3, 4, 5};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int result2 = count_bidirectional_pairs(arr2, size2);
    printf("Array 2 bidirectional pairs: %d\n", result2);
    
    int arr3[] = {5, 5, 5, 5};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    
    int result3 = count_bidirectional_pairs(arr3, size3);
    printf("Array 3 bidirectional pairs: %d\n", result3);
    
    int arr4[] = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    
    int result4 = count_bidirectional_pairs(arr4, size4);
    printf("Array 4 bidirectional pairs: %d\n", result4);
    
    return 0;
}