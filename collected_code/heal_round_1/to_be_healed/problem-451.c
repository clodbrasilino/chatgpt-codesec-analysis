#include <stdio.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

void removeWhitespace(char *str) {
    regex_t regex;
    const char *pattern = "[[:space:]]";
    
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex pattern\n");
        return;
    }
    
    /* Possible weaknesses found:
     *  implicit declaration of function 'regreplace' [-Wimplicit-function-declaration]
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  initialization of 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    char *output = regreplace(str, regex, "", REG_EXTENDED);
    printf("%s", output);
    regfree(&regex);
    /* Possible weaknesses found:
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(output);
}

int main() {
    char str[] = "Hello World! How are you?";
    removeWhitespace(str);
    return 0;
}