#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_five_char_words(const char *text) {
    if (text == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    const char *p = text;

    reti = regcomp(&regex, "\\b[a-zA-Z]{5}\\b", REG_EXTENDED);
    if (reti) {
        return;
    }

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        int length = end - start;

        char *word = (char *)malloc((length + 1) * sizeof(char));
        if (word != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, p + start, length);
            word[length] = '\0';
            printf("%s\n", word);
            free(word);
        }
        
        p += end;
    }

    regfree(&regex);
}

int main() {
    const char *sample_text = "This is a quick brown fox jumps over the lazy dog and tiger";
    find_five_char_words(sample_text);
    return 0;
}