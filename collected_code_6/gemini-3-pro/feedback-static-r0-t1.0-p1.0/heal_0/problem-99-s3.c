#include <stdio.h>
#include <stdlib.h>

void decimalToBinary(int n, char **binaryStr) {
    if (n == 0) {
        *binaryStr = malloc(2 * sizeof(char));
        if (*binaryStr == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        (*binaryStr)[0] = '0';
        (*binaryStr)[1] = '\0';
        return;
    }

    int temp = n;
    int length = 0;
    while (temp > 0) {
        length++;
        temp /= 2;
    }

    *binaryStr = malloc((length + 1) * sizeof(char));
    if (*binaryStr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    (*binaryStr)[length] = '\0';
    
    for (int i = length - 1; i >= 0; i--) {
        (*binaryStr)[i] = (n % 2) + '0';
        n /= 2;
    }
}

int main(void) {
    int decimalNumber;
    char *binaryString = NULL;

    if (scanf("%d", &decimalNumber) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (decimalNumber < 0) {
        fprintf(stderr, "Negative numbers are not supported\n");
        return EXIT_FAILURE;
    }

    decimalToBinary(decimalNumber, &binaryString);

    if (binaryString != NULL) {
        printf("%s\n", binaryString);
        free(binaryString);
        binaryString = NULL;
    }

    return EXIT_SUCCESS;
}