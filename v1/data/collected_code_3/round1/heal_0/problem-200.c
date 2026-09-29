#include <stdio.h>
#include <stdlib.h>

void find_max_positions(int* arr, int len) {
    int max = arr[0];
    int i;
    for(i = 1; i < len; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    printf("Max value is %d at positions: ", max);
    for(i = 0; i < len; i++) {
        if(arr[i] == max) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int len = sizeof(arr) / sizeof(arr[0]);
    find_max_positions(arr, len);
    return 0;
}