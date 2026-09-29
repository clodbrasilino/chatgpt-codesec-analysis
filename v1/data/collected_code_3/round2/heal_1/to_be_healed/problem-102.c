#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* snakeToCamel(char* snake_str) {
    int i, j = 0;
    int len = strlen(snake_str);
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    char* camel_str = (char*)malloc(sizeof(char) * len);

    for(i = 0; i < len; i++) {
        if(snake_str[i] == '_') {
            i++;
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'camel_str' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            camel_str[j] = toupper(snake_str[i]);
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'camel_str' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            camel_str[j] = snake_str[i];
        }
        j++;
    }
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'camel_str' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    camel_str[j] = '\0';
    return camel_str;
}

int main() {
    char snake_str[100];
    printf("Enter a snake case string: ");
    scanf("%s", snake_str);
    char* camel_str = snakeToCamel(snake_str);
    printf("Camel case string: %s\n", camel_str);
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(camel_str);
    return 0;
}