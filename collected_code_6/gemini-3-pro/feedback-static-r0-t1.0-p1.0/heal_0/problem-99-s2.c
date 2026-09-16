#include <stdio.h>
#include <stdlib.h>

void decimalToBinary(int n) {
    if (n < 0) {
        printf("Error: Please enter a non-negative integer.\n");
        return;
    }

    if (n == 0) {
        printf("0\n");
        return;
    }

    int *binaryNum = (int *)malloc(32 * sizeof(int));
    if (binaryNum == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binaryNum[j]);
    }
    printf("\n");

    free(binaryNum);
}

int main() {
    int num;
    
    if (scanf("%d", &num) != 1) {
        printf("Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    decimalToBinary(num);

    return EXIT_SUCCESS;
}