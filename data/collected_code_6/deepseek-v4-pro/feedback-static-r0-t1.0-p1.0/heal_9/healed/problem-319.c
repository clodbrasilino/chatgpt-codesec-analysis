#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

void find_five_char_words(const char *str) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "\\b[A-Za-z]{5}\\b";
    const char *cursor;
    int result;
    size_t str_len;

    if (str == NULL) {
        fprintf(stderr, "Input string is NULL\n");
        return;
    }

    str_len = strnlen(str, 4096);
    if (str_len >= 4096) {
        fprintf(stderr, "Input string too long or not null-terminated\n");
        return;
    }

    cursor = str;

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t cursor_offset = (size_t)(cursor - str);

        if (cursor_offset > str_len) {
            regfree(&regex);
            fprintf(stderr, "Buffer overflow prevented\n");
            return;
        }

        size_t cursor_remaining = str_len - cursor_offset;

        if (match.rm_so > match.rm_eo) {
            regfree(&regex);
            fprintf(stderr, "Invalid match boundaries\n");
            return;
        }

        if (match.rm_so > cursor_remaining || match.rm_eo > cursor_remaining) {
            regfree(&regex);
            fprintf(stderr, "Buffer overflow prevented\n");
            return;
        }

        size_t word_len = match.rm_eo - match.rm_so;

        if (word_len == 0) {
            cursor += match.rm_eo;
            continue;
        }

        if (word_len >= 4096) {
            cursor += match.rm_eo;
            continue;
        }

        if (word_len > SIZE_MAX - 1) {
            regfree(&regex);
            fprintf(stderr, "Integer overflow detected\n");
            return;
        }

        char *word = (char *)malloc(word_len + 1);
        if (word == NULL) {
            regfree(&regex);
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }

        memcpy(word, cursor + match.rm_so, word_len);
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