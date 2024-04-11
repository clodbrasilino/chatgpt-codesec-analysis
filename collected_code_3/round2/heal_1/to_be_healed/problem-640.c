#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* removeParenthesis(char* str) {
    int i, j = 0, count = 0;
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    char* result = (char*)malloc(strlen(str) + 1);

    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] == '(') {
            count++;
            continue;
        } else if(str[i] == ')') {
            count--;
            continue;
        }

        if(count == 0) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[j] = str[i];
            j++;
        }
    }

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    result[j] = '\0';
    return result;
}

int main() {
    char str[] = "Hello (world)!";
    char* result = removeParenthesis(str);
    printf("%s\n", result);
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(result);
    return 0;
}