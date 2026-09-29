#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* snakeToCamel(char* snakeStr) {
    int i, j = 0;
    int len = strlen(snakeStr);
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    char* camelStr = (char*)malloc(sizeof(char) * len);

    for(i = 0; i < len; i++) {
        if(snakeStr[i] == '_') {
            i++;
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'camelStr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            camelStr[j] = toupper(snakeStr[i]);
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'camelStr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            camelStr[j] = snakeStr[i];
        }
        j++;
    }
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'camelStr' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    camelStr[j] = '\0';
    return camelStr;
}

int main() {
    char snakeStr[100];
    printf("Enter a snake case string: ");
    scanf("%s", snakeStr);
    char* camelStr = snakeToCamel(snakeStr);
    printf("Camel case string: %s\n", camelStr);
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(camelStr);
    return 0;
}