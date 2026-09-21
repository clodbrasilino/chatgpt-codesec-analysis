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
        regerror(reti, &regex, NULL, 0);
        /* Possible weaknesses found:
         *  passing argument 3 of 'regerror' from incompatible pointer type [-Wincompatible-pointer-types]
         */
        regerror(reti, &regex, &msglen, sizeof(msglen));
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