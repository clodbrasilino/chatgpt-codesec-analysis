#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_long_words(const char *text) {
    if (!text) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    const char *p = text;

    reti = regcomp(&regex, "\\b[a-zA-Z0-9_]{4,}\\b", REG_EXTENDED);
    if (reti) {
        return;
    }

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        int len = end - start;

        char *word = (char *)malloc(len + 1);
        if (word != NULL) {
            snprintf(word, len + 1, "%.*s", len, p + start);
            printf("%s\n", word);
            free(word);
        }

        p += end;
    }

    regfree(&regex);
}

int main(void) {
    const char *sample_text = "This is a sample text with some long words and short ones.";
    find_long_words(sample_text);
    return 0;
}