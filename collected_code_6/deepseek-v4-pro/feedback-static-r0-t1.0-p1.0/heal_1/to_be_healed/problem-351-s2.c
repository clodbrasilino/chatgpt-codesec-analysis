#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE 100000

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int firstElementKTimes(int arr[], int n, int k) {
    if (k <= 0) return -1;
    
    int *count = (int *)calloc(MAX_VALUE, sizeof(int));
    if (count == NULL) return -1;
    
    int *first_occurrence = (int *)malloc(MAX_VALUE * sizeof(int));
    if (first_occurrence == NULL) {
        free(count);
        return -1;
    }
    
    for (int i = 0; i < MAX_VALUE; i++) {
        first_occurrence[i] = -1;
    }
    
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0 || arr[i] >= MAX_VALUE) continue;
        
        count[arr[i]]++;
        if (first_occurrence[arr[i]] == -1) {
            first_occurrence[arr[i]] = i;
        }
    }
    
    int result = -1;
    int min_index = n;
    
    for (int i = 0; i < MAX_VALUE; i++) {
        if (count[i] == k && first_occurrence[i] != -1) {
            if (first_occurrence[i] < min_index) {
                min_index = first_occurrence[i];
                result = i;
            }
        }
    }
    
    free(count);
    free(first_occurrence);
    
    return result;
}

int main() {
    int arr1[] = {1, 7, 4, 3, 4, 8, 7};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 2;
    printf("First element occurring %d times: %d\n", k1, firstElementKTimes(arr1, n1, k1));
    
    int arr2[] = {4, 1, 6, 1, 6, 4};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 1;
    printf("First element occurring %d times: %d\n", k2, firstElementKTimes(arr2, n2, k2));
    
    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int k3 = 3;
    printf("First element occurring %d times: %d\n", k3, firstElementKTimes(arr3, n3, k3));
    
    return 0;
}