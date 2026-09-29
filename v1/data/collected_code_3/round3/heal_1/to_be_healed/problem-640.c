#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* removeParenthesis(char* str) {
    int i = 0, j = 0;
    int inParenthesis = 0;
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    char *result = malloc(strlen(str) + 1);

    while(str[i]) {
        if(str[i] == '(') {
            inParenthesis = 1;
        } else if(str[i] == ')') {
            inParenthesis = 0;
            i++;
            continue;
        }
        if(!inParenthesis) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[j++] = str[i];
        }
        i++;
    }
    result[j] = '\0';
    return result;
}

int main() {
    char str[] = "Hello (world)!";
    char *result = removeParenthesis(str);
    printf("%s\n", result);
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(result);
    return 0;
}