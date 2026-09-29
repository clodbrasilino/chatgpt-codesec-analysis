#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_five_char_words(const char *str) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "\\b[A-Za-z]{5}\\b";
    const char *cursor = str;
    int result;

    if (str == NULL) {
        fprintf(stderr, "Input string is NULL\n");
        return;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo < 0) {
            break;
        }
        
        size_t len = match.rm_eo - match.rm_so;
        if (len == 0) {
            break;
        }
        
        if (len >= SIZE_MAX) {
            regfree(&regex);
            fprintf(stderr, "Invalid length for allocation\n");
            return;
        }
        
        char *word = (char *)malloc(len + 1);
        if (word == NULL) {
            regfree(&regex);
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        
        if (len >= len + match.rm_so || match.rm_so > SIZE_MAX - len) {
            free(word);
            regfree(&regex);
            fprintf(stderr, "Integer overflow detected\n");
            return;
        }
        
        memcpy(word, cursor + match.rm_so, len);
        word[len] = '\0';
        
        printf("%s\n", word);
        
        free(word);
        cursor += match.rm_eo;
    }

    regfree(&regex);
}

int main(int argc, char * const *argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    find_five_char_words(argv[1]);
    return EXIT_SUCCESS;
}