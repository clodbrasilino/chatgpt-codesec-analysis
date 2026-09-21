#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

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
        /* Possible weaknesses found:
         *  possible fix: dereference with '*'
         *  incompatible pointer to integer conversion passing 'size_t *' (aka 'unsigned long *') to parameter of type 'size_t' (aka 'unsigned long'); remove & [-Wint-conversion]
         *  passing argument 4 of 'regerror' makes integer from pointer without a cast [-Wint-conversion]
         */
        regerror(reti, &regex, NULL, &msglen);
        char *msgbuf = malloc(msglen + 1);
        if (msgbuf) {
            regerror(reti, &regex, msgbuf, msglen + 1);
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
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