#include <stdio.h>
#include <regex.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int match_pattern(const char *str) {
    regex_t regex;
    int reti;
    size_t msgbuf_size = regerror(0, &regex, NULL, 0);
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *msgbuf = malloc(msgbuf_size);
    
    if (!msgbuf) {
        perror("malloc failed");
        return 1;
    }

    reti = regcomp(&regex, "^a.*b$", REG_EXTENDED);
    if (reti) {
        regerror(reti, &regex, msgbuf, msgbuf_size);
        fprintf(stderr, "Could not compile regex: %s\n", msgbuf);
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(msgbuf);
        return 1;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        regfree(&regex);
        free(msgbuf);
        return 1;
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
        free(msgbuf);
        return 0;
    } else {
        regerror(reti, &regex, msgbuf, msgbuf_size);
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        free(msgbuf);
        return 1;
    }
}

int main() {
    const char *test_strings[] = {"ab", "aab", "acb", "acbb", "abcd", "a_b", "axb"};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        if (match_pattern(test_strings[i])) {
            printf("Matched: %s\n", test_strings[i]);
        } else {
            printf("Not matched: %s\n", test_strings[i]);
        }
    }
    return 0;
}