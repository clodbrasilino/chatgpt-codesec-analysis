#include <stdio.h>
#include <stdbool.h>

bool checkOddIndexOddNumbers(int arr[], int n) {
    for (int i = 1; i < n; i += 2) {
        if (arr[i] % 2 == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 3, 2, 5, 4, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (checkOddIndexOddNumbers(arr, n)) {
        printf("Every odd index contains odd numbers.\n");
    } else {
        printf("Every odd index does not contain odd numbers.\n");
    }

    return 0;
}