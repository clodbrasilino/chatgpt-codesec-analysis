#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_ERROR_MSG 256

int search_literal(const char *text, const char *literal, size_t *offset)
{
    regex_t regex;
    regmatch_t match;
    char error_msg[MAX_ERROR_MSG] = {0};
    int ret;

    if (text == NULL || literal == NULL || offset == NULL) {
        return -1;
    }

    ret = regcomp(&regex, literal, REG_NEWLINE);
    if (ret != 0) {
        regerror(ret, &regex, error_msg, sizeof(error_msg));
        error_msg[sizeof(error_msg) - 1] = '\0';
        fprintf(stderr, "regcomp failed: %s\n", error_msg);
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

    regerror(ret, &regex, error_msg, sizeof(error_msg));
    error_msg[sizeof(error_msg) - 1] = '\0';
    fprintf(stderr, "regexec failed: %s\n", error_msg);
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