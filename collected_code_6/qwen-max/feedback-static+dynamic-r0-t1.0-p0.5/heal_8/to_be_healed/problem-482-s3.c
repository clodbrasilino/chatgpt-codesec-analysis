#include <stdio.h>
#include <regex.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void find_sequences(const char *input) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    reti = regexec(&regex, input, 0, NULL, 0);
    if (!reti) {
        printf("Match found\n");
    } else if (reti == REG_NOMATCH) {
        printf("No match found\n");
    } else {
        size_t msglen;
        regerror(reti, &regex, NULL, 0);
        /* Possible weaknesses found:
         *  passing argument 3 of 'regerror' from incompatible pointer type [-Wincompatible-pointer-types]
         */
        regerror(reti, &regex, &msglen, sizeof(msglen));
        /* Possible weaknesses found:
         *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
         *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
         */
        char *msgbuf = malloc(msglen + 1);
        if (msgbuf) {
            regerror(reti, &regex, msgbuf, msglen + 1);
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            /* Possible weaknesses found:
             *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include '<stdlib.h>' or provide a declaration of 'free'
             *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
             *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
             */
            free(msgbuf);
        }
    }

    regfree(&regex);
}

int main() {
    const char *test_string = "This is a TestString with SomeSequences and some without";
    find_sequences(test_string);
    return 0;
}