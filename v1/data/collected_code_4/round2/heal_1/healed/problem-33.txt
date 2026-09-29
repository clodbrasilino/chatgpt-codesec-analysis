#include <stdio.h>
#include <stdlib.h>

int * decimalToBinary(int num) {
    int index = 0; 
    int *binary = malloc(sizeof(int) * 32);

    if (binary != NULL){
        while (num > 0) {
            binary[index++] = num % 2;
            num = num / 2;
        }
        while(index < 32){
            binary[index++] = 0;
        }

        return binary;
    } else {
        return NULL;
    }
}

int main() {
    int number, i;
    printf("Enter any number: ");
    scanf("%d", &number);
    int *binary = decimalToBinary(number);
    if(binary != NULL){
        for(i = 31; i >= 0; i--) {
            printf("%d", binary[i]);
        }
        printf("\n");
        free(binary);
    }

    return 0;
}