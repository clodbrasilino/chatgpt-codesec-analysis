#include <stdio.h>

void find_even(int *arr, int n) {
    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 == 0)
            printf("%d\n", arr[i]);
    }
}

int main() {
    int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int n = sizeof(arr)/sizeof(arr[0][0]);
    for(int i = 0; i < 3; i++)
        find_even(arr[i], n);
    return 0;
}