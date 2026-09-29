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
    
    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        int len = end - start;

        char *word = (char *)malloc(len + 1);
        if (word != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, p + start, len);
            word[len] = '\0';
            printf("%s\n", word);
            free(word);
        }

        p += end;
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "This is a quick brown foxes jumps over the lazy tiger.";
    find_five_char_words(text);
    return 0;
}