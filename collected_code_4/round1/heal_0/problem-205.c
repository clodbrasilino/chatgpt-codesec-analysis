#include<stdio.h>

int getInversionCount(int arr[], int n) {
    int inv_count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                inv_count++;
            }
        }
    }
    return inv_count;
}

int main() {
    int tuple_list[] = {1, 20, 6, 4, 5};
    int n = sizeof(tuple_list) / sizeof(tuple_list[0]);
    printf("Number of inversions are %d \n", getInversionCount(tuple_list, n));
    return 0;
}