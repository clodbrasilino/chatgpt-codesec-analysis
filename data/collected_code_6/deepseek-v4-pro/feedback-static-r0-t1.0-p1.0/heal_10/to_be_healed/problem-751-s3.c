#include <stdio.h>
#include <stdbool.h>

bool is_min_heap(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return false;
    }
    
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[i] > arr[left]) {
            return false;
        }
        
        if (right < n && arr[i] > arr[right]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int heap1[] = {2, 3, 5, 7, 6, 8, 10};
    int heap2[] = {2, 10, 5, 7, 6, 8, 3};
    int heap3[] = {5};
    int heap4[] = {10, 5, 8, 3, 2};
    
    int n1 = sizeof(heap1) / sizeof(heap1[0]);
    int n2 = sizeof(heap2) / sizeof(heap2[0]);
    int n3 = sizeof(heap3) / sizeof(heap3[0]);
    int n4 = sizeof(heap4) / sizeof(heap4[0]);
    
    printf("Array1 is %s\n", is_min_heap(heap1, n1) ? "a min heap" : "not a min heap");
    printf("Array2 is %s\n", is_min_heap(heap2, n2) ? "a min heap" : "not a min heap");
    printf("Array3 is %s\n", is_min_heap(heap3, n3) ? "a min heap" : "not a min heap");
    printf("Array4 is %s\n", is_min_heap(heap4, n4) ? "a min heap" : "not a min heap");
    
    const int *null_array = NULL;
    /* Possible weaknesses found:
     *  Assignment 'result=is_min_heap(null_array,0)', assigned value is 0
     *  Calling function 'is_min_heap' returns 0
     */
    bool result = is_min_heap(null_array, 0);
    /* Possible weaknesses found:
     *  Condition '!result' is always true [knownConditionTrueFalse]
     *  Condition '!result' is always true
     */
    if (!result) {
        printf("NULL array is not a min heap\n");
    } else {
        printf("NULL array is a min heap\n");
    }
    
    return 0;
}