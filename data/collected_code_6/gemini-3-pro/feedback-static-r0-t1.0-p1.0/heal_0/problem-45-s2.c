#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int findArrayGCD(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    int result = arr[0];
    for (size_t i = 1; i < size; i++) {
        result = gcd(result, arr[i]);
        if (result == 1) {
            break;
        }
    }
    return result;
}

int main(void) {
    int arr[] = {24, 36, 48, 60};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = findArrayGCD(arr, size);
    
    printf("%d\n", result);

    return EXIT_SUCCESS;
}