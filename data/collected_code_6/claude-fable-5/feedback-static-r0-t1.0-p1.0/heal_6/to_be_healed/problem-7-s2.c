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

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t start;
        size_t end;
        size_t length;
        size_t bufsize;
        char *word;

        /* Possible weaknesses found:
         *  Assuming that condition 'match.rm_eo<=match.rm_so' is not redundant
         */
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            break;
        }

        /* Possible weaknesses found:
         *  start is assigned '(unsigned long)match.rm_so' here.
         */
        start = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Assignment 'end=(unsigned long)match.rm_eo', assigned value is less than symbolic=start
         */
        end = (size_t)match.rm_eo;

        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (end > remaining || start > remaining) {
            break;
        }

        /* Possible weaknesses found:
         *  Assignment 'length=end-start', assigned value is less than 0
         */
        length = end - start;
        /* Possible weaknesses found:
         *  Condition 'length>remaining-start' is always false [knownConditionTrueFalse]
         *  Condition 'length>remaining-start' is always false
         */
        if (length > remaining - start) {
            break;
        }

        /* Possible weaknesses found:
         *  bufsize is assigned 'length+1' here.
         */
        bufsize = length + 1;
        /* Possible weaknesses found:
         *  Condition 'bufsize<length' is always false
         *  Condition 'bufsize<length' is always false [knownConditionTrueFalse]
         */
        if (bufsize < length) {
            break;
        }

        word = malloc(bufsize);
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

        if (remaining == 0 || *cursor == '\0') {
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