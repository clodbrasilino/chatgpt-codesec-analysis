#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LITERAL_LEN 511

static char *escape_literal(const char *literal)
{
    size_t len;
    size_t i;
    size_t j = 0;
    char *buffer;

    if (literal == NULL) {
        return NULL;
    }

    len = strnlen(literal, MAX_LITERAL_LEN + 1);
    if (len > MAX_LITERAL_LEN) {
        return NULL;
    }

    buffer = calloc((len * 2) + 1, sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (strchr(".^$*+?()[]{}|\\", literal[i]) != NULL) {
            buffer[j++] = '\\';
        }
        buffer[j++] = literal[i];
    }
    buffer[j] = '\0';

    return buffer;
}

static void print_regex_error(int code, const regex_t *regex, const char *prefix)
{
    size_t needed;
    char *errbuf;

    needed = regerror(code, regex, NULL, 0);
    if (needed == 0) {
        fprintf(stderr, "%s: unknown error\n", prefix);
        return;
    }

    errbuf = calloc(needed, sizeof(char));
    if (errbuf == NULL) {
        fprintf(stderr, "%s: memory allocation failure\n", prefix);
        return;
    }

    regerror(code, regex, errbuf, needed);
    errbuf[needed - 1] = '\0';
    fprintf(stderr, "%s: %s\n", prefix, errbuf);
    free(errbuf);
}

int search_pattern(const char *text, const char *literal, long *start, long *end)
{
    regex_t regex;
    regmatch_t match;
    char *escaped;
    int ret;

    if (text == NULL || literal == NULL || start == NULL || end == NULL) {
        return -1;
    }

    escaped = escape_literal(literal);
    if (escaped == NULL) {
        return -1;
    }

    ret = regcomp(&regex, escaped, REG_EXTENDED);
    free(escaped);
    if (ret != 0) {
        print_regex_error(ret, &regex, "regcomp failed");
        return -1;
    }

    ret = regexec(&regex, text, 1, &match, 0);
    if (ret == 0) {
        *start = (long)match.rm_so;
        *end = (long)match.rm_eo;
        regfree(&regex);
        return 0;
    } else if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 1;
    } else {
        print_regex_error(ret, &regex, "regexec failed");
        regfree(&regex);
        return -1;
    }
}

int main(void)
{
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *literal = "brown fox";
    long start = 0;
    long end = 0;
    int result;

    result = search_pattern(text, literal, &start, &end);

    if (result == 0) {
        printf("Pattern \"%s\" found in text.\n", literal);
        printf("Match starts at index %ld and ends at index %ld.\n", start, end - 1);
    } else if (result == 1) {
        printf("Pattern \"%s\" not found in text.\n", literal);
    } else {
        fprintf(stderr, "An error occurred during pattern search.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}