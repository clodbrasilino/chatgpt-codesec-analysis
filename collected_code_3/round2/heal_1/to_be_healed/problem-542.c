#include <stdio.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'exit'
  */

void replace_with_colon(char *str) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "[ ,.]", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         *  implicit declaration of function 'exit' [-Wimplicit-function-declaration]
         */
        exit(1);
    }

    int i = 0;
    while (str[i]) {
        reti = regexec(&regex, &str[i], 0, NULL, 0);
        if (!reti) {
            str[i] = ':';
        }
        i++;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_with_colon(str);
    printf("%s\n", str);
    return 0;
}