#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool areAllCharactersUnique(const char* str) {
    int charCount[256] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        if (charCount[(unsigned char)str[i]] > 0) {
            return false;
        }
        charCount[(unsigned char)str[i]]++;
    }

    return true;
}

int main() {
    const char* str1 = "Hello, world!";
    const char* str2 = "abcdef";

    if (areAllCharactersUnique(str1))
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("All characters in str1 are unique\n");
    else
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("All characters in str1 are not unique\n");

    if (areAllCharactersUnique(str2))
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("All characters in str2 are unique\n");
    else
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("All characters in str2 are not unique\n");

    return 0;
}