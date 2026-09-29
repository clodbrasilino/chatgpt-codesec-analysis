#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_words(const char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "\\b[a-zA-Z]\\{3,5\\}\\b";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    const char *cursor = str;
    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        int len = end - start;
        
        char *word = malloc(len + 1);
        if (word != NULL) {
            memcpy(word, cursor + start, len);
            word[len] = '\0';
            printf("%s\n", word);
            free(word);
        }
        
        cursor += end;
    }

    regfree(&regex);
}

int main() {
    const char *text = "The quick brown fox jumps over the lazy dog in a sunny day";
    find_words(text);
    return 0;
}