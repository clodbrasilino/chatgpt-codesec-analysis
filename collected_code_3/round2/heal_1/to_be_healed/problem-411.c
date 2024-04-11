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
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    char* camel = malloc(len+1);

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
    char snake[] = "this_is_a_snake_case_string";
    char* camel = snakeToCamel(snake);
    printf("%s\n", camel);
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(camel);
    return 0;
}