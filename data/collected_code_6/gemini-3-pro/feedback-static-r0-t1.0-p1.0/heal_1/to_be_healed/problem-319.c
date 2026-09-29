#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_five_char_words(const char *input_string) {
    if (input_string == NULL) {
        return;
    }

    regex_t regex;
    regmatch_t pmatch[1];
    int reti;

    reti = regcomp(&regex, "\\b[a-zA-Z]{5}\\b", REG_EXTENDED);
    if (reti != 0) {
        return;
    }

    const char *p = input_string;
    /* Possible weaknesses found:
     *  Although the value stored to 'reti' is used in the enclosing expression, the value is never actually read from 'reti' [deadcode.DeadStores]
     */
    while ((reti = regexec(&regex, p, 1, pmatch, 0)) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        int len = end - start;

        char *word = (char *)malloc(len + 1);
        if (word != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(word, p + start, len);
            word[len] = '\0';
            printf("%s\n", word);
            free(word);
        }

        p += end;
    }

    regfree(&regex);
}

int main() {
    const char *text = "This is a quick brown foxes jumps over the lazy tiger.";
    find_five_char_words(text);
    return 0;
}