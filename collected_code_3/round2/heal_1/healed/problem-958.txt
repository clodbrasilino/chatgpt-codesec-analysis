#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* intToRoman(int num) {

    char* roman = (char*)calloc(16, sizeof(char));
    if (roman == NULL) {
        return NULL;
    }

    char* symbol[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    int value[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    int i = 0;

    while(num != 0) {
        while(num >= value[i]) {
            num -= value[i];
            strcat(roman, symbol[i]);
        }
        i++;
    }

    return roman;
}

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    char* roman = intToRoman(num);

    if (roman != NULL) {
        printf("Roman numeral: %s\n", roman);
        free(roman);
    } else {
        printf("Memory allocation failed.\n");
        return 1;
    }

    return 0;
}