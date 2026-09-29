#include <stdio.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'exit'
  */

void find_sequence(char *str) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "[A-Z][a-z]*", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         *  implicit declaration of function 'exit' [-Wimplicit-function-declaration]
         */
        exit(1);
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        puts("Match");
    } else if (reti == REG_NOMATCH) {
        puts("No match");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         */
        exit(1);
    }

    regfree(&regex);
}

int main() {
    char str[] = "HelloWorld";
    find_sequence(str);
    return 0;
}