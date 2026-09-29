#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex, const char *context)
{
    size_t errbuf_size;
    char *errbuf;

    errbuf_size = regerror(errcode, regex, NULL, 0);
    errbuf = malloc(errbuf_size);
    if (errbuf != NULL) {
        regerror(errcode, regex, errbuf, errbuf_size);
        fprintf(stderr, "%s: %s\n", context, errbuf);
        free(errbuf);
    } else {
        fprintf(stderr, "%s: unable to allocate error buffer\n", context);
    }
}

int search_pattern(const char *text, const char *pattern, regoff_t *start, regoff_t *end)
{
    regex_t regex;
    regmatch_t match;
    int ret;

    if (text == NULL || pattern == NULL || start == NULL || end == NULL) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "Regex compilation failed");
        return -1;
    }

    ret = regexec(&regex, text, 1, &match, 0);
    if (ret == 0) {
        *start = match.rm_so;
        *end = match.rm_eo;
        regfree(&regex);
        return 0;
    } else if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 1;
    } else {
        print_regex_error(ret, &regex, "Regex execution failed");
        regfree(&regex);
        return -1;
    }
}

int main(void)
{
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "brown fox";
    regoff_t start = 0;
    regoff_t end = 0;
    int result;

    result = search_pattern(text, pattern, &start, &end);

    if (result == 0) {
        printf("Pattern \"%s\" found in string.\n", pattern);
        printf("Match starts at index %ld and ends at index %ld.\n",
               (long)start, (long)end);
        printf("Matched substring: \"%.*s\"\n",
               (int)(end - start), text + start);
    } else if (result == 1) {
        printf("Pattern \"%s\" not found in string.\n", pattern);
    } else {
        fprintf(stderr, "An error occurred during pattern search.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}