#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str) {
    regex_t regex;
    regcomp(&regex, "[ ,.]", 0);
    /* Possible weaknesses found:
     *  implicit declaration of function 'regreplace' [-Wimplicit-function-declaration]
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    regreplace(&regex, str, ":", str, 0);
    regfree(&regex);
}

int main() {
    char str[] = "This is a string, with spaces and commas.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}