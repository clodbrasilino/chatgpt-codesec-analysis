#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex, const char *prefix)
{
    size_t needed = regerror(errcode, regex, NULL, 0);
    char *error_msg = malloc(needed);

    if (error_msg == NULL) {
        fprintf(stderr, "%s: unable to allocate memory for error message\n", prefix);
        return;
    }

    regerror(errcode, regex, error_msg, needed);
    fprintf(stderr, "%s: %s\n", prefix, error_msg);
    free(error_msg);
}

int search_literal(const char *text, const char *literal, size_t *offset)
{
    regex_t regex;
    regmatch_t match;
    int ret;

    if (text == NULL || literal == NULL || offset == NULL) {
        return -1;
    }

    ret = regcomp(&regex, literal, REG_NEWLINE);
    if (ret != 0) {
        print_regex_error(ret, &regex, "regcomp failed");
        return -1;
    }

    ret = regexec(&regex, text, 1, &match, 0);
    if (ret == 0) {
        *offset = (size_t)match.rm_so;
        regfree(&regex);
        return 1;
    }

    if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    }

    print_regex_error(ret, &regex, "regexec failed");
    regfree(&regex);
    return -1;
}

int main(void)
{
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *literals[] = { "quick", "fox", "cat", "lazy" };
    size_t count = sizeof(literals) / sizeof(literals[0]);
    size_t i;
    size_t offset = 0;
    int status = EXIT_SUCCESS;

    for (i = 0; i < count; i++) {
        int result = search_literal(text, literals[i], &offset);
        if (result == 1) {
            printf("Found \"%s\" at offset %zu\n", literals[i], offset);
        } else if (result == 0) {
            printf("\"%s\" not found\n", literals[i]);
        } else {
            fprintf(stderr, "Error searching for \"%s\"\n", literals[i]);
            status = EXIT_FAILURE;
        }
    }

    return status;
}