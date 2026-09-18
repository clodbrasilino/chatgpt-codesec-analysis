#include <stdio.h>

void find_values(int arr[], int size, int num) {
    for(int i=0; i<size; i++) {
        if(arr[i] > num) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int num = 25;
    
    find_values(arr, size, num);

    return 0;
}