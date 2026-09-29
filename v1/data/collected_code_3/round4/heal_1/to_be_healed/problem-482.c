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
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
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
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         */
        exit(1);
    }

    regfree(&regex);
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0';
    find_sequence(str);
    return 0;
}