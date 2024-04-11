#include <stdio.h>

int sumXOR(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < 32; i++) {
        int zc = 0, oc = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] % 2 == 0)
                zc++;
            else
                oc++;
            arr[j] /= 2;
        }
        sum += (zc * oc * (1 << i));
    }
    return sum;
}

int main() {
    int arr[] = {5, 9, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Sum of XOR of all pairs is %d", sumXOR(arr, n));
    return 0;
}