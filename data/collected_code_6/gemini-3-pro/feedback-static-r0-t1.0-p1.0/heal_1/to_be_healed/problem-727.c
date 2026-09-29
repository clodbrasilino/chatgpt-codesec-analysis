#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>

void filter_alphanumeric(const char *input, char **output) {
    if (!input || !output) {
        return;
    }

    regex_t regex;
    int ret;
    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        *output = NULL;
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    *output = (char *)malloc(len + 1);
    char *out_ptr = *output;

    if (!*output) {
        regfree(&regex);
        return;
    }

    regmatch_t pmatch[1];
    const char *p = input;

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;

        for (size_t i = 0; i < match_start; ++i) {
            *out_ptr++ = p[i];
        }
        
        p += match_end;
    }

    while (*p != '\0') {
        *out_ptr++ = *p++;
    }
    *out_ptr = '\0';

    regfree(&regex);
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output = NULL;

    filter_alphanumeric(input, &output);

    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error processing string or memory allocation failed.\n");
    }

    return 0;
}