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
    size_t input_len;
    size_t out_capacity;
    size_t out_len = 0;
    size_t offset = 0;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    out_capacity = (input_len * 2U) + 1U;

    output = malloc(out_capacity);
    if (output == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0) {
        free(output);
        return NULL;
    }

    while (offset < input_len) {
        ret = regexec(&regex, input + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = input_len - offset;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + out_len, input + offset, remaining);
            out_len += remaining;
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
        memcpy(output + out_len, input + offset, (size_t)match.rm_so);
        out_len += (size_t)match.rm_so;

        if ((offset + (size_t)match.rm_so) > 0U) {
            output[out_len] = '_';
            out_len++;
        }

        output[out_len] = (char)tolower((unsigned char)input[offset + (size_t)match.rm_so]);
        out_len++;

        offset += (size_t)match.rm_eo;
    }

    output[out_len] = '\0';
    regfree(&regex);
    return output;
}

int main(void)
{
    const char *tests[] = {
        "camelCaseString",
        "ConvertThisToSnake",
        "alreadylower",
        "XMLParser",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *result = camel_to_snake(tests[i]);
        if (result == NULL) {
            fprintf(stderr, "Conversion failed for input: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (printf("%s -> %s\n", tests[i], result) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
        free(result);
    }

    return EXIT_SUCCESS;
}