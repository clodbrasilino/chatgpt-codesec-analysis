#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_words(const char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    const char *pattern = "\\b[a-zA-Z]{3,5}\\b";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return;
    }

    const char *p = str;
    while (1) {
        reti = regexec(&regex, p, 1, pmatch, 0);
        if (reti != 0) {
            break;
        }

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
    const char *text = "This is a test string with words of various lengths like cat, dog, apple, and horse.";
    find_words(text);
    return 0;
}