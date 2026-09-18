#include <stdio.h>
#include <stdlib.h>

int findPlatform(int arr[], int dep[], int n) {
    int i = 1, j = 0, platforms_needed = 1, count = 1;
    while(i < n && j < n) {
        if(arr[i] <= dep[j]) {
            count++;
            i++;
        } else if(arr[i] > dep[j]) {
            count--;
            j++;
        }
        if(count > platforms_needed) {
            platforms_needed = count;
        }
    }
    return platforms_needed;
}

int compare(const void* a, const void* b) { 
    return *(int*)a - *(int*)b; 
}

int main() {
    int arr[] = {9, 9, 9, 10, 10, 11, 15, 16, 17};
    int dep[] = {11, 11, 12, 12, 13, 15, 17, 18, 19};
    int n = sizeof(arr)/sizeof(arr[0]);
    qsort(arr, n, sizeof(int), compare);
    qsort(dep, n, sizeof(int), compare);
    printf("Minimum platforms required: %d", findPlatform(arr, dep, n));
    return 0;
}