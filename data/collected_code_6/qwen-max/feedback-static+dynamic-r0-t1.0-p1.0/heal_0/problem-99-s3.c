#include <stdio.h>
#include <stdlib.h>

void decimalToBinary(int n) {
    int binaryNum[32];
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binaryNum[j]);
    }
}

int main() {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    decimalToBinary(num);
    return EXIT_SUCCESS;
}