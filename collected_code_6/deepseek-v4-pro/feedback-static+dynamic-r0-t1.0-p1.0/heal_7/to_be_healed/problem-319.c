#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

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
        
        if (match.rm_eo <= match.rm_so) {
            break;
        }
        
        size_t len = (size_t)(match.rm_eo - match.rm_so);
        
        if (len > SIZE_MAX - 1) {
            regfree(&regex);
            fprintf(stderr, "Invalid length for allocation\n");
            return;
        }
        
        if (match.rm_so < 0 || (size_t)match.rm_so > SIZE_MAX - len) {
            regfree(&regex);
            fprintf(stderr, "Integer overflow detected\n");
            return;
        }
        
        char *word = (char *)malloc(len + 1);
        if (word == NULL) {
            regfree(&regex);
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t src_len = strlen(cursor + match.rm_so);
        if (src_len < len) {
            free(word);
            regfree(&regex);
            fprintf(stderr, "Source data smaller than expected\n");
            return;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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