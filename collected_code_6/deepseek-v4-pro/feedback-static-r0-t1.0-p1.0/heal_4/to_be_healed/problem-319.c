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
    size_t str_len;

    if (str == NULL) {
        fprintf(stderr, "Input string is NULL\n");
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    str_len = strlen(str);

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t word_len = match.rm_eo - match.rm_so;
        size_t cursor_remaining = str_len - (size_t)(cursor - str);

        if (match.rm_so > cursor_remaining || word_len > cursor_remaining - match.rm_so) {
            regfree(&regex);
            fprintf(stderr, "Buffer overflow prevented\n");
            return;
        }

        char *word = (char *)malloc(word_len + 1);
        if (word == NULL) {
            regfree(&regex);
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }

        if (word_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, cursor + match.rm_so, word_len);
        }
        word[word_len] = '\0';
        printf("%s\n", word);
        free(word);
        cursor += match.rm_eo;
    }

    regfree(&regex);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    find_five_char_words(argv[1]);
    return EXIT_SUCCESS;
}