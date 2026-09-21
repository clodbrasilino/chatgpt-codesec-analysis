#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *camel_to_snake(const char *input);

char *camel_to_snake(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *output = NULL;
    const char *cursor = NULL;
    size_t out_len = 0;
    size_t in_len = 0;
    int ret = 0;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    in_len = strlen(input);

    output = malloc((in_len * 2U) + 1U);
    if (output == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0) {
        free(output);
        return NULL;
    }

    cursor = input;
    out_len = 0;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t rest = strlen(cursor);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(&output[out_len], cursor, rest);
            out_len += rest;
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(&output[out_len], cursor, (size_t)match.rm_so);
        out_len += (size_t)match.rm_so;

        if (cursor != input || match.rm_so > 0) {
            output[out_len] = '_';
            out_len++;
        }

        output[out_len] = (char)tolower((unsigned char)cursor[match.rm_so]);
        out_len++;

        cursor += match.rm_eo;
    }

    output[out_len] = '\0';
    regfree(&regex);

    return output;
}

int main(void)
{
    const char *tests[] = {
        "camelCaseString",
        "ThisIsATest",
        "already_snake",
        "simpleXMLParser",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i = 0;

    for (i = 0; i < count; i++) {
        char *result = camel_to_snake(tests[i]);
        if (result == NULL) {
            fprintf(stderr, "Conversion failed for: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("%s -> %s\n", tests[i], result);
        free(result);
    }

    return EXIT_SUCCESS;
}