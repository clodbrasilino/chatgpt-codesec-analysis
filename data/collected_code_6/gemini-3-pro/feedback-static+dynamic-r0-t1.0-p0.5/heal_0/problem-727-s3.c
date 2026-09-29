#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alphanumeric(const char *input, char **output) {
    if (!input || !output) {
        return -1;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    size_t len = strlen(input);
    *output = (char *)malloc(len + 1);
    if (!*output) {
        regfree(&regex);
        return -1;
    }

    regmatch_t pmatch[1];
    const char *cursor = input;
    char *out_cursor = *output;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;

        if (match_start > 0) {
            memcpy(out_cursor, cursor, match_start);
            out_cursor += match_start;
        }

        cursor += match_end;
    }

    size_t remaining = strlen(cursor);
    if (remaining > 0) {
        memcpy(out_cursor, cursor, remaining);
        out_cursor += remaining;
    }

    *out_cursor = '\0';

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output = NULL;

    if (remove_non_alphanumeric(input, &output) == 0) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}