#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

void replace_chars(char* str) {
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == ' ') {
            str[i] = '_';
        } else if(str[i] == '_') {
            str[i] = ' ';
        }
    }
}

int main() {
    char str[] = "Hello_World this is_a_test";
    replace_chars(str);
    /* Possible weaknesses found:
     *  include '<stdio.h>' or provide a declaration of 'printf'
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     */
    printf("%s", str);
    return 0;
}