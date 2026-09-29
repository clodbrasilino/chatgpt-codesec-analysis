#include <stdio.h>

int find_count(int arr[], int n, int record) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] == record) {
            return count;
        }
        count++;
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int record = 5;
    int result = find_count(arr, n, record);
    if(result != -1) {
        printf("The element count that occurs before the record is: %d\n", result);
    } else {
        printf("Record not found in the array.\n");
    }
    return 0;
}