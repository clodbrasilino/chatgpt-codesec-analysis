#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t len;
    size_t out;
    size_t offset;
    int rc;

    if (input == NULL) {
        return NULL;
    }

    rc = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (rc != 0) {
        return NULL;
    }

    len = strlen(input);
    result = malloc((2U * len) + 1U);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    out = 0U;
    offset = 0U;
    while ((offset < len) &&
           (regexec(&regex, input + offset, 1U, &match, 0) == 0)) {
        size_t start = offset + (size_t)match.rm_so;
        memcpy(result + out, input + offset, (size_t)match.rm_so);
        out += (size_t)match.rm_so;
        if ((start > 0U) && (input[start - 1U] != ' ')) {
            result[out] = ' ';
            out++;
        }
        result[out] = input[start];
        out++;
        offset = start + 1U;
    }

    memcpy(result + out, input + offset, len - offset);
    out += len - offset;
    result[out] = '\0';

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *text = "HelloWorldThisIsATestString";
    char *spaced;

    spaced = add_spaces(text);
    if (spaced == NULL) {
        fprintf(stderr, "Failed to process input string\n");
        return EXIT_FAILURE;
    }

    printf("Input : %s\n", text);
    printf("Output: %s\n", spaced);

    free(spaced);
    return EXIT_SUCCESS;
}