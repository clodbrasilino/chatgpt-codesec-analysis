#include <stdio.h>

void findNumbers(int arr[], int size, int m, int n) {
    for (int i = 0; i < size; i++) {
        if ((arr[i] % m == 0) || (arr[i] % n == 0)) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int numbers[] = { 5, 10, 15, 20, 25, 30 };
    int m = 10;
    int n = 15;
    int size = sizeof(numbers) / sizeof(numbers[0]);

    findNumbers(numbers, size, m, n);

    return 0;
}