#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *camel_to_snake(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *output;
    char *shrunk;
    size_t input_len;
    size_t capacity;
    size_t out_pos = 0;
    size_t offset = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ret' can be reduced. [variableScope]
     */
    int ret;

    if (input == NULL) {
        return NULL;
    }

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    capacity = (input_len * 2) + 1;

    output = malloc(capacity);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (offset < input_len) {
        ret = regexec(&regex, input + offset, 1, &match, 0);

        if (ret == REG_NOMATCH) {
            size_t remaining = input_len - offset;
            if (out_pos + remaining >= capacity) {
                free(output);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + out_pos, input + offset, remaining);
            out_pos += remaining;
            break;
        }

        if (ret != 0) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        if (out_pos + (size_t)match.rm_so + 2 >= capacity) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + out_pos, input + offset, (size_t)match.rm_so);
        out_pos += (size_t)match.rm_so;

        if (offset + (size_t)match.rm_so > 0) {
            output[out_pos++] = '_';
        }
        output[out_pos++] = (char)tolower((unsigned char)input[offset + (size_t)match.rm_so]);

        offset += (size_t)match.rm_so + 1;
    }

    output[out_pos] = '\0';
    regfree(&regex);

    shrunk = realloc(output, out_pos + 1);
    if (shrunk != NULL) {
        output = shrunk;
    }

    return output;
}

int main(void)
{
    const char *tests[] = {
        "camelCaseString",
        "thisIsATest",
        "helloWorld",
        "convertCamelCaseToSnakeCase",
        "simple",
        "already_snake",
        ""
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        char *snake = camel_to_snake(tests[i]);
        if (snake == NULL) {
            fprintf(stderr, "Conversion failed for input: \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("Input:  %s\nOutput: %s\n\n", tests[i], snake);
        free(snake);
    }

    return EXIT_SUCCESS;
}