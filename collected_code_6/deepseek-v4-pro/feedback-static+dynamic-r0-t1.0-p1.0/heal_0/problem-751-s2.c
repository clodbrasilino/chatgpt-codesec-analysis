#include <stdio.h>
#include <stdbool.h>

bool is_min_heap(const int arr[], int n, int i) {
    if (i >= n) return true;
    
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] < arr[i]) return false;
    if (right < n && arr[right] < arr[i]) return false;
    
    return is_min_heap(arr, n, left) && is_min_heap(arr, n, right);
}

bool check_min_heap(const int arr[], int n) {
    if (arr == NULL || n <= 0) return false;
    
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left] < arr[i]) return false;
        if (right < n && arr[right] < arr[i]) return false;
    }
    
    return true;
}

int main(void) {
    int heap1[] = {2, 3, 4, 5, 10, 15};
    int heap2[] = {2, 10, 4, 5, 3, 15};
    int heap3[] = {1};
    int heap4[] = {10, 5, 3};
    int heap5[] = {5, 10, 15, 20, 25};
    
    int n1 = sizeof(heap1) / sizeof(heap1[0]);
    int n2 = sizeof(heap2) / sizeof(heap2[0]);
    int n3 = sizeof(heap3) / sizeof(heap3[0]);
    int n4 = sizeof(heap4) / sizeof(heap4[0]);
    int n5 = sizeof(heap5) / sizeof(heap5[0]);
    
    printf("heap1 is %s\n", check_min_heap(heap1, n1) ? "min heap" : "not min heap");
    printf("heap2 is %s\n", check_min_heap(heap2, n2) ? "min heap" : "not min heap");
    printf("heap3 is %s\n", check_min_heap(heap3, n3) ? "min heap" : "not min heap");
    printf("heap4 is %s\n", check_min_heap(heap4, n4) ? "min heap" : "not min heap");
    printf("heap5 is %s\n", check_min_heap(heap5, n5) ? "min heap" : "not min heap");
    
    printf("recursive heap1 is %s\n", is_min_heap(heap1, n1, 0) ? "min heap" : "not min heap");
    printf("recursive heap2 is %s\n", is_min_heap(heap2, n2, 0) ? "min heap" : "not min heap");
    printf("recursive heap3 is %s\n", is_min_heap(heap3, n3, 0) ? "min heap" : "not min heap");
    printf("recursive heap4 is %s\n", is_min_heap(heap4, n4, 0) ? "min heap" : "not min heap");
    printf("recursive heap5 is %s\n", is_min_heap(heap5, n5, 0) ? "min heap" : "not min heap");
    
    return 0;
}