#include <stdio.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void addSpaces(char *str) {
    regex_t regex;
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    char *newStr = malloc(strlen(str) * 2);
    int i, j = 0;

    regcomp(&regex, "[A-Z]", 0);

    for(i = 0; i < strlen(str); i++) {
        if(regexec(&regex, &str[i], 0, NULL, 0) == 0 && i != 0) {
            newStr[j++] = ' ';
        }
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'newStr' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        newStr[j++] = str[i];
    }

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newStr' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newStr[j] = '\0';
    strcpy(str, newStr);
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(newStr);
    regfree(&regex);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    addSpaces(str);
    printf("%s\n", str);
    return 0;
}