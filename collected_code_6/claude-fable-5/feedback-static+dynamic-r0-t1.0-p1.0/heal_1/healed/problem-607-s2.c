#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LITERAL_LEN 511
#define ESCAPED_BUFFER_SIZE 1024
#define ERRBUF_SIZE 256

static int escape_literal(const char *literal, char *buffer, size_t buffer_size)
{
    size_t j = 0;
    size_t i;
    size_t len;

    if (literal == NULL || buffer == NULL || buffer_size == 0) {
        return -1;
    }

    len = strnlen(literal, MAX_LITERAL_LEN + 1);
    if (len > MAX_LITERAL_LEN) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        if (strchr(".^$*+?()[]{}|\\", literal[i]) != NULL) {
            if (j + 2 >= buffer_size) {
                return -1;
            }
            buffer[j++] = '\\';
            buffer[j++] = literal[i];
        } else {
            if (j + 1 >= buffer_size) {
                return -1;
            }
            buffer[j++] = literal[i];
        }
    }

    if (j >= buffer_size) {
        return -1;
    }
    buffer[j] = '\0';
    return 0;
}

int search_pattern(const char *text, const char *literal, long *start, long *end)
{
    regex_t regex;
    regmatch_t match;
    char escaped[ESCAPED_BUFFER_SIZE];
    int ret;

    if (text == NULL || literal == NULL || start == NULL || end == NULL) {
        return -1;
    }

    memset(escaped, 0, sizeof(escaped));

    if (escape_literal(literal, escaped, sizeof(escaped)) != 0) {
        return -1;
    }

    ret = regcomp(&regex, escaped, REG_EXTENDED);
    if (ret != 0) {
        char errbuf[ERRBUF_SIZE];
        memset(errbuf, 0, sizeof(errbuf));
        regerror(ret, &regex, errbuf, sizeof(errbuf) - 1);
        errbuf[sizeof(errbuf) - 1] = '\0';
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
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
        char errbuf[ERRBUF_SIZE];
        memset(errbuf, 0, sizeof(errbuf));
        regerror(ret, &regex, errbuf, sizeof(errbuf) - 1);
        errbuf[sizeof(errbuf) - 1] = '\0';
        fprintf(stderr, "regexec failed: %s\n", errbuf);
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