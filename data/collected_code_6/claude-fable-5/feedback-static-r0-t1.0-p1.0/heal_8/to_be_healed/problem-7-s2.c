#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 4096

static void print_regex_error(int errcode, const regex_t *regex)
{
    size_t needed;
    char *errbuf;

    needed = regerror(errcode, regex, NULL, 0);
    if (needed == 0) {
        fprintf(stderr, "Regex compilation failed: unknown error\n");
        return;
    }

    errbuf = malloc(needed);
    if (errbuf == NULL) {
        fprintf(stderr, "Regex compilation failed: unable to allocate error buffer\n");
        return;
    }

    (void)regerror(errcode, regex, errbuf, needed);
    errbuf[needed - 1] = '\0';
    fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
    free(errbuf);
}

int find_long_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;
    size_t remaining;

    if (text == NULL) {
        return -1;
    }

    remaining = strnlen(text, MAX_INPUT_LENGTH);
    if (remaining >= MAX_INPUT_LENGTH && text[MAX_INPUT_LENGTH - 1] != '\0') {
        fprintf(stderr, "Input exceeds maximum allowed length\n");
        return -1;
    }

    ret = regcomp(&regex, "[[:alpha:]]{4,}", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex);
        return -1;
    }

    cursor = text;

    while (remaining > 0 && regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t start;
        size_t end;
        size_t length;
        char *word;

        if (match.rm_so < 0 || match.rm_eo < 0) {
            break;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        if (end <= start || end > remaining) {
            break;
        }

        length = end - start;

        if (length >= (size_t)-1 || length > remaining - start) {
            break;
        }

        word = malloc(length + 1);
        if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, cursor + start, length);
        word[length] = '\0';
        printf("%s\n", word);
        free(word);

        cursor += end;
        remaining -= end;

        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "The quick brown fox jumps over a lazy dog near it";

    if (find_long_words(input) != 0) {
        fprintf(stderr, "Failed to process input string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}