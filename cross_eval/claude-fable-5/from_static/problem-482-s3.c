#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex, const char *prefix)
{
    size_t needed = regerror(errcode, regex, NULL, 0);
    char *errbuf = malloc(needed);

    if (errbuf == NULL) {
        fprintf(stderr, "%s: unable to allocate error buffer\n", prefix);
        return;
    }

    regerror(errcode, regex, errbuf, needed);
    fprintf(stderr, "%s: %s\n", prefix, errbuf);
    free(errbuf);
}

int find_sequences(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;

    if (text == NULL) {
        fprintf(stderr, "Input string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "Regex compilation failed");
        return -1;
    }

    cursor = text;
    while ((ret = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        int length = (int)(match.rm_eo - match.rm_so);
        printf("Found: %.*s\n", length, cursor + match.rm_so);
        if (match.rm_eo == 0) {
            break;
        }
        cursor += match.rm_eo;
    }

    if (ret != REG_NOMATCH && ret != 0) {
        print_regex_error(ret, &regex, "Regex execution failed");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *test_string = "Hello world This is a Test String with Multiple Sequences";

    if (find_sequences(test_string) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}