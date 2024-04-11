#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool areAllCharactersUnique(char* str) {
    int chars[256] = {0};

    for(int i = 0; i < strlen(str); i++) {
        if(chars[(int)str[i]] == 1) {
            return false;
        }
        chars[(int)str[i]] = 1;
    }

    return true;
}

int main() {
    char str[] = "Hello, World!";
    if(areAllCharactersUnique(str)) {
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("All characters are unique.\n");
    } else {
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  include '<stdio.h>' or provide a declaration of 'printf'
         */
        printf("All characters are not unique.\n");
    }

    return 0;
}