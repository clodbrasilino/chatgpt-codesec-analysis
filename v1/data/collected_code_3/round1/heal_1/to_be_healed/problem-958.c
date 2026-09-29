#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcat'
  */

char* intToRoman(int num) {
    char* roman = (char*)malloc(sizeof(char) * 16);
    char* symbol[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    int value[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    int i = 0;
    while(num != 0) {
        while(num >= value[i]) {
            num -= value[i];
            /* Possible weaknesses found:
             *  implicit declaration of function 'strcat' [-Wimplicit-function-declaration]
             *  use of possibly-NULL 'roman' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
             *  include '<string.h>' or provide a declaration of 'strcat'
             *  incompatible implicit declaration of built-in function 'strcat' [-Wbuiltin-declaration-mismatch]
             */
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
    printf("Roman numeral: %s\n", roman);
    free(roman);
    return 0;
}