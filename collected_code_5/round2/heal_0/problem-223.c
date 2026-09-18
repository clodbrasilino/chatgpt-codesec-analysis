#include <stdbool.h>
#include <stdio.h>

bool isMajority(int arr[], int n, int num) {
    int i;

    for (i = 0; i <= n / 2; i++) {
        if (arr[i] == num && arr[i + n / 2] == num)
            return true;
    }

    return false;
}

int main() {
    int arr[] = {1, 2, 2, 3, 2, 2, 2}, n = 7;
    int candidate = arr[n / 2];

    if (isMajority(arr, n, candidate)) {
        printf("%d is the majority element\n", candidate);
    } else {
        printf("No majority Element\n");
    }
    return 0;
}