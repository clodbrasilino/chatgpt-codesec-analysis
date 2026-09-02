#include <stdio.h>
#include <stdlib.h>

void printLuckyNumbers(int n) {
    if (n <= 0) return;

    int *numbers = (int *)malloc((n + 1) * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i <= n; i++) {
        numbers[i] = 2 * i + 1;
    }

    int idx = 1;
    while (idx < n) {
        int step = numbers[idx];
        for (int i = idx; i <= n - step; i += step) {
            int temp = numbers[i];
            numbers[i] = numbers[i + step - 1];
            numbers[i + step - 1] = temp;
        }
        idx++;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    free(numbers);
}

int main() {
    int n;
    printf("Enter the number of lucky numbers to print: ");
    scanf("%d", &n);

    printLuckyNumbers(n);
    return 0;
}