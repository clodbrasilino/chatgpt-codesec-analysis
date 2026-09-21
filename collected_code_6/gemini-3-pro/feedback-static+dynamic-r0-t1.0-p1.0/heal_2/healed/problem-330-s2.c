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
    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        int len = end - start;

        if (len > 0) {
            char *word = (char *)malloc(len + 1);
            if (word == NULL) {
                regfree(&regex);
                return;
            }

            snprintf(word, len + 1, "%.*s", len, p + start);
            
            printf("%s\n", word);
            free(word);
        }

        p += end;
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "A cat and a mouse were playing in the garden with their friend dog.";
    find_words(text);
    return 0;
}