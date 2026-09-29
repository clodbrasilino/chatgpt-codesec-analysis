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

int replace_with_colon(char *str)
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
        print_regex_error(ret, &regex, "Regex compilation failed");
        return -1;
    }

    cursor = str;
    while ((ret = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        cursor[match.rm_so] = ':';
        cursor += match.rm_eo;
    }

    if (ret != REG_NOMATCH) {
        print_regex_error(ret, &regex, "Regex execution failed");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    char input[] = "Hello World, this is a test. Goodbye.";

    printf("Original: %s\n", input);

    if (replace_with_colon(input) != 0) {
        fprintf(stderr, "Replacement failed\n");
        return EXIT_FAILURE;
    }

    printf("Modified: %s\n", input);

    return EXIT_SUCCESS;
}