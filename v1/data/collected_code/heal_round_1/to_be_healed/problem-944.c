#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isdigit'
  */

void separateAndPrintNumbers(char* string) {
    int count = 0;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'string[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; string[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'isdigit' [-Wimplicit-function-declaration]
         *  Cannot determine that 'string[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (isdigit(string[i])) {
            /* Possible weaknesses found:
             *  Cannot determine that 'string[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("Number: %c, Position: %d\n", string[i], i);
            count++;
        }
    }
    
    printf("Total numbers found: %d\n", count);
}

int main() {
    char string[] = "ab12cd34ef56";
    
    separateAndPrintNumbers(string);
    
    return 0;
}