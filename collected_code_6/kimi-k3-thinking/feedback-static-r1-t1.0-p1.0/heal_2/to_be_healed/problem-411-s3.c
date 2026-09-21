#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *snake_to_camel(const char *input, size_t input_len)
{
    regex_t regex;
    regmatch_t match[1];
    char *result;
    size_t pos;
    size_t i;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "_([a-zA-Z0-9])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    pos = 0;
    i = 0;

    while (pos < input_len) {
        match[0].rm_so = 0;
        match[0].rm_eo = (regoff_t)(input_len - pos);

        ret = regexec(&regex, input + pos, 1, match, REG_STARTEND);
        if (ret == 0) {
            size_t offset = (size_t)match[0].rm_so;
            size_t match_end = (size_t)match[0].rm_eo;

            if (offset > input_len - pos || match_end > input_len - pos ||
                match_end < offset + 2 || offset > input_len - i) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + i, input + pos, offset);
            i += offset;
            result[i++] = (char)toupper((unsigned char)input[pos + offset + 1]);
            pos += match_end;
        } else if (ret == REG_NOMATCH) {
            size_t rest = input_len - pos;

            if (rest > input_len - i) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + i, input + pos, rest);
            i += rest;
            break;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    result[i] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *tests[] = {
        "hello_world",
        "snake_case_string",
        "convert_this_to_camel",
        "already",
        NULL
    };
    size_t t;

    for (t = 0; tests[t] != NULL; t++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        char *camel = snake_to_camel(tests[t], strlen(tests[t]));
        if (camel == NULL) {
            fprintf(stderr, "Conversion failed for: %s\n", tests[t]);
            return EXIT_FAILURE;
        }
        printf("%s -> %s\n", tests[t], camel);
        free(camel);
    }

    return EXIT_SUCCESS;
}