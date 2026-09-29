#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool check_if_string_is_integer(const char* str) {
    if (str == NULL) {
        return false;
    }

    if (*str == '-' || *str == '+') {
        ++str;
    }

    while (*str != '\0') {
        if (!isdigit((unsigned char)*str)) {
            return false;
        }
        ++str;
    }
    
    return true;
}

int main(int argc, char **argv) {
    const char *str = "12345";
    if(check_if_string_is_integer(str)) {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("The string represents an integer.\n");
    } else {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("The string does not represent an integer.\n");
    }

    return 0;
}