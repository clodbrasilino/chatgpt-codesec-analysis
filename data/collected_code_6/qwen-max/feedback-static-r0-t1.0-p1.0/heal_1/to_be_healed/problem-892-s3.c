#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isspace'
  */

void remove_multiple_spaces(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        *dst++ = *src++;
        /* Possible weaknesses found:
         *  call to undeclared library function 'isspace' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'isspace' [-Wimplicit-function-declaration]
         *  include the header <ctype.h> or explicitly provide a declaration for 'isspace'
         */
        if (isspace((unsigned char)*src) && isspace((unsigned char)dst[-1])) {
            while (isspace((unsigned char)*src)) src++;
        }
    }
    *dst = '\0';
}

int main() {
    char input[] = "This  is   a    test";
    remove_multiple_spaces(input);
    printf("%s\n", input);
    return 0;
}