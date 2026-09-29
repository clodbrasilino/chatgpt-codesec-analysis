#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int remove_whitespace(char *string)
{
    regex_t regex;
    regmatch_t match;
    size_t offset = 0;
    int status;

    if (string == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    while ((status = regexec(&regex, string + offset, 1, &match, 0)) == 0) {
        size_t start = offset + (size_t)match.rm_so;
        size_t end = offset + (size_t)match.rm_eo;

        memmove(string + start, string + end, strlen(string + end) + 1);
        offset = start;
    }

    regfree(&regex);
    return status == REG_NOMATCH ? 0 : -1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result = EXIT_FAILURE;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (remove_whitespace(line) == 0) {
        if (printf("%s\n", line) >= 0) {
            result = EXIT_SUCCESS;
        }
    }

    free(line);
    return result;
}