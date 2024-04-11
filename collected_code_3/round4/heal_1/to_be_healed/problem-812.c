#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* abbreviateRoad(char* str) {
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    char* result = malloc(strlen(str) + 1);
    char* token = strtok(str, " ");
    while (token != NULL) {
        if (strcmp(token, "road") == 0) {
            strcat(result, "rd. ");
        } else {
            strcat(result, token);
            strcat(result, " ");
        }
        token = strtok(NULL, " ");
    }
    return result;
}

int main() {
    char str[] = "I live on a long road";
    char* result = abbreviateRoad(str);
    /* Possible weaknesses found:
     *  use of possibly-NULL 'result' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
     */
    printf("%s\n", result);
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(result);
    return 0;
}