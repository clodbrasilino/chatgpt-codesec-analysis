#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_long_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;

    if (text == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[[:alpha:]]{4,}", REG_EXTENDED);
    if (ret != 0) {
        size_t errlen = regerror(ret, &regex, NULL, 0);
        char *errbuf = malloc(errlen);
        if (errbuf != NULL) {
            regerror(ret, &regex, errbuf, errlen);
            fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
            free(errbuf);
        } else {
            fprintf(stderr, "Regex compilation failed\n");
        }
        return -1;
    }

    cursor = text;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            break;
        }

        size_t remaining = strlen(cursor);
        if ((size_t)match.rm_eo > remaining) {
            break;
        }

        size_t length = (size_t)(match.rm_eo - match.rm_so);
        size_t bufsize = length + 1;

        char *word = malloc(bufsize);
        if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return -1;
        }

        if (length >= bufsize) {
            free(word);
            regfree(&regex);
            return -1;
        }

        memcpy(word, cursor + match.rm_so, length);
        word[length] = '\0';
        printf("%s\n", word);
        free(word);

        cursor += match.rm_eo;
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