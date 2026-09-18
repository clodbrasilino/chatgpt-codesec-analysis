#include <stdio.h>
#include<string.h>

char* intToRoman(int num) {
    char roman[13][3] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    int decimal[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1}; 
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    char *res = malloc(sizeof(char) * 16);
    memset(res, 0, sizeof(char) * 16);
    int i = 0;
    while(num){
      while(num >= decimal[i]){
         num -= decimal[i];
         strcat(res, roman[i]);
      }
      i++;
    }
    return res;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    char *roman = intToRoman(number);
    if(roman) {
        printf("Roman numeral: %s\n", roman);
        /* Possible weaknesses found:
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        free(roman);
    }
    return 0;
}