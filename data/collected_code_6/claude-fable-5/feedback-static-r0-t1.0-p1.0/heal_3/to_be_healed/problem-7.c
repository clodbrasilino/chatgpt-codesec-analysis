#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERRBUF_SIZE 256

static void print_regex_error(int errcode, const regex_t *regex, const char *prefix)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[ERRBUF_SIZE];

    memset(errbuf, 0, sizeof(errbuf));
    regerror(errcode, regex, errbuf, sizeof(errbuf) - 1);
    errbuf[sizeof(errbuf) - 1] = '\0';
    fprintf(stderr, "%s: %s\n", prefix, errbuf);
}

int find_long_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;

    if (text == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[A-Za-z]{4,}", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "regcomp failed");
        return -1;
    }

    cursor = text;
    while ((ret = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            break;
        }

        size_t length = (size_t)(match.rm_eo - match.rm_so);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = strlen(cursor);

        if ((size_t)match.rm_eo > remaining) {
            break;
        }

        char *word = malloc(length + 1);
        if (word == NULL) {
            fprintf(stderr, "malloc failed\n");
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, cursor + match.rm_so, length);
        word[length] = '\0';
        printf("%s\n", word);
        free(word);

        cursor += match.rm_eo;
        if (*cursor == '\0') {
            break;
        }
    }

    if (ret != 0 && ret != REG_NOMATCH) {
        print_regex_error(ret, &regex, "regexec failed");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *text = "The quick brown fox jumps over a lazy dog";

    if (find_long_words(text) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}