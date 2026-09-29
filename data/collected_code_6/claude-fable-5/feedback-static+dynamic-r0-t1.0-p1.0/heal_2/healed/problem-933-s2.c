#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096U

char *camel_to_snake(const char *input);

char *camel_to_snake(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *output = NULL;
    const char *cursor = NULL;
    size_t out_len = 0;
    size_t in_len = 0;
    size_t out_cap = 0;
    int ret = 0;

    if (input == NULL) {
        return NULL;
    }

    in_len = strnlen(input, MAX_INPUT_LEN);
    if (in_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    out_cap = (in_len * 2U) + 1U;
    output = malloc(out_cap);
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
            size_t rest = strnlen(cursor, MAX_INPUT_LEN);
            if (rest >= out_cap || out_len >= (out_cap - rest)) {
                regfree(&regex);
                free(output);
                return NULL;
            }
            memcpy(&output[out_len], cursor, rest);
            out_len += rest;
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        if (((size_t)match.rm_so + 2U) >= out_cap ||
            out_len >= (out_cap - ((size_t)match.rm_so + 2U))) {
            regfree(&regex);
            free(output);
            return NULL;
        }

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

    if (out_len >= out_cap) {
        regfree(&regex);
        free(output);
        return NULL;
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