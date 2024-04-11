#include <stdio.h>
#include <stdbool.h>

bool isLinear(int arr[], int n) {
    if(n == 1)
        return true;

    int diff = arr[1] - arr[0];
    for(int i = 2; i < n; i++) {
        if(arr[i] - arr[i-1] != diff)
            return false;
    }
    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    if(isLinear(arr, n))
        printf("The sequence is linear.\n");
    else
        printf("The sequence is not linear.\n");

    return 0;
}