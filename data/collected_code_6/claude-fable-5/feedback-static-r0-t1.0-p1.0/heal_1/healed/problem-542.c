#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex, const char *prefix)
{
    size_t needed;
    char *errbuf;

    needed = regerror(errcode, regex, NULL, 0);
    errbuf = malloc(needed);
    if (errbuf == NULL) {
        fprintf(stderr, "%s: unable to allocate error buffer\n", prefix);
        return;
    }
    regerror(errcode, regex, errbuf, needed);
    fprintf(stderr, "%s: %s\n", prefix, errbuf);
    free(errbuf);
}

static int replace_with_colon(char *str)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    char *cursor;

    if (str == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "regcomp failed");
        return -1;
    }

    cursor = str;
    while ((ret = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            break;
        }
        cursor[match.rm_so] = ':';
        cursor += match.rm_eo;
    }

    if (ret != REG_NOMATCH && ret != 0) {
        print_regex_error(ret, &regex, "regexec failed");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    char text[] = "Hello, world. This is a test string.";

    printf("Before: %s\n", text);

    if (replace_with_colon(text) != 0) {
        fprintf(stderr, "Replacement failed\n");
        return EXIT_FAILURE;
    }

    printf("After:  %s\n", text);

    return EXIT_SUCCESS;
}