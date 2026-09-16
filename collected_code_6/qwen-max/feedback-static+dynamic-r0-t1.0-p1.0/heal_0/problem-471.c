#include <stdio.h>
#include <stdlib.h>

unsigned long long find_remainder(int *arr, size_t len, unsigned int n) {
    unsigned long long result = 1;
    for (size_t i = 0; i < len; ++i) {
        result = (result * arr[i]) % n;
    }
    return result;
}

int main() {
    int arr[] = {10, 20, 30, 40};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    unsigned int n = 17;
    unsigned long long remainder = find_remainder(arr, len, n);
    printf("The remainder is: %llu\n", remainder);
    return 0;
}