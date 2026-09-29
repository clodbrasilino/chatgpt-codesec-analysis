#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_words_by_length(const char *input, int min_len, int max_len) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "\\b[a-zA-Z]{3,5}\\b";
    int ret;
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    const char *cursor = input;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        int word_len = match.rm_eo - match.rm_so;
        if (word_len >= min_len && word_len <= max_len) {
            printf("%.*s\n", word_len, cursor + match.rm_so);
        }
        cursor += match.rm_eo;
        if (match.rm_so == match.rm_eo) {
            cursor++;
        }
    }
    
    regfree(&regex);
}

int main() {
    const char *text = "The quick brown fox jumps over the lazy dog. This is a test string with various word lengths.";
    
    printf("Words with 3-5 characters:\n");
    find_words_by_length(text, 3, 5);
    
    return 0;
}