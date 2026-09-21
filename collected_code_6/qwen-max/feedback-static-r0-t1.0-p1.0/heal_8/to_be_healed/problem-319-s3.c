#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void find_five_char_words(const char *string) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, "\\b\\w{5}\\b", REG_EXTENDED|REG_NEWLINE)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    reti = regexec(&regex, string, 0, NULL, 0);
    if (!reti) {
        regfree(&regex);
        printf("Found a word of five characters\n");
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
        return;
    } else {
        size_t msgbuf_size;
        /* Possible weaknesses found:
         *  incompatible pointer to integer conversion passing 'size_t *' (aka 'unsigned long *') to parameter of type 'size_t' (aka 'unsigned long'); dereference with * [-Wint-conversion]
         *  possible fix: dereference with '*'
         *  passing argument 4 of 'regerror' makes integer from pointer without a cast [-Wint-conversion]
         */
        regerror(reti, &regex, NULL, (size_t *)&msgbuf_size);
        char *msgbuf = malloc(msgbuf_size + 1);
        if (msgbuf != NULL) {
            regerror(reti, &regex, msgbuf, msgbuf_size + 1);
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            free(msgbuf);
        }
        regfree(&regex);
    }
}

int main() {
    const char *input = "This is a test with apple and stone.";
    find_five_char_words(input);
    return 0;
}