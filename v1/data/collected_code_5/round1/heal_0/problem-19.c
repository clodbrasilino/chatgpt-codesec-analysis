#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int compare(const void * a, const void * b) {
   return (*(int*)a - *(int*)b);
}

bool containsDuplicates(int arr[], int len) {
    qsort(arr, len, sizeof(int), compare);
    for (int i = 0; i < len-1; i++) {
        if (arr[i] == arr[i + 1]) {
            return true;
        }
    }
    return false;
}

int main() {
    int arr[] = {1,2,3,4,5,6,7,1};
    int len = sizeof(arr) / sizeof(arr[0]);

    if (containsDuplicates(arr, len))
        printf("Duplicates found in array.\n");
    else
        printf("No Duplicates found in array.\n");

    return 0;
}