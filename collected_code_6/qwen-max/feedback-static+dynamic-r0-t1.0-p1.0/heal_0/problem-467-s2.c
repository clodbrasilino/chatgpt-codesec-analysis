#include <stdio.h>
#include <stdlib.h>

char* decimalToOctal(long int num) {
    char *octal = (char *)malloc(22 * sizeof(char));
    if (octal == NULL) {
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (num != 0) {
        octal[i] = (num % 8) + '0';
        num /= 8;
        i++;
    }
    if (i == 0) {
        octal[i++] = '0';
    }
    octal[i] = '\0';
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = octal[j];
        octal[j] = octal[k];
        octal[k] = temp;
    }
    return octal;
}

int main() {
    long int num;
    printf("Enter a decimal number: ");
    if (scanf("%ld", &num) != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    char *octal = decimalToOctal(num);
    printf("Octal: %s\n", octal);
    free(octal);
    return 0;
}