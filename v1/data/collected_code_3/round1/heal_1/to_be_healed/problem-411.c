#include <stdio.h>
#include <ctype.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* snakeToCamel(char* snake) {
    int i, j = 0;
    int len = strlen(snake);
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    char* camel = malloc(len * sizeof(char));

    for(i = 0; i < len; i++) {
        if(snake[i] == '_') {
            i++;
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'camel' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            camel[j] = toupper(snake[i]);
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'camel' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            camel[j] = snake[i];
        }
        j++;
    }
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'camel' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    camel[j] = '\0';
    return camel;
}

int main() {
    char snake[] = "this_is_snake_case";
    char* camel = snakeToCamel(snake);
    printf("%s\n", camel);
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(camel);
    return 0;
}