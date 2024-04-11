#include <stdio.h>
#include <stdlib.h>

char* intToRoman(int num) {
    char* result = (char*)malloc(sizeof(char) * 16);
    char* symbols[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    int values[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    int i = 0;

    while(num > 0) {
        while(num >= values[i]) {
            num -= values[i];
            strcat(result, symbols[i]);
        }
        i++;
    }
    return result;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    char* roman = intToRoman(num);
    printf("Roman numeral: %s\n", roman);
    free(roman);
    return 0;
}