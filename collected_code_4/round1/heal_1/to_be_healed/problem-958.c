#include <stdio.h>
#include<string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* intToRoman(int num) {
    char roman[13][3] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    int decimal[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1}; 
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
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
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
         */
        free(roman);
    }
    return 0;
}