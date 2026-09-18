#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool isInteger(const char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    if (*str == '+' || *str == '-') {
        str++;
    }
    
    while (*str != '\0') {
        if (!isdigit(*str)) {
            return false;
            str++;
        }
    }
    
    return true;
}

int main() {
    const char *str = "-1234";
    if (isInteger(str)) {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("The string is an integer.\n");
    } else {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("The string is not an integer.\n");
    }
    
    return 0;
}