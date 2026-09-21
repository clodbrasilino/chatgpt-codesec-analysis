#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096U

static int safe_append(char *dest, size_t *dest_len, size_t dest_cap,
                       const char *src, size_t src_len);
char *camel_to_snake(const char *input);

static int safe_append(char *dest, size_t *dest_len, size_t dest_cap,
                       const char *src, size_t src_len)
{
    size_t i;

    if (dest == NULL || dest_len == NULL || src == NULL) {
        return -1;
    }
    if (dest_cap == 0U) {
        return -1;
    }
    if (src_len > (dest_cap - 1U) || *dest_len > ((dest_cap - 1U) - src_len)) {
        return -1;
    }
    for (i = 0; i < src_len; i++) {
        dest[*dest_len + i] = src[i];
    }
    *dest_len += src_len;
    return 0;
}

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
            if (safe_append(output, &out_len, out_cap, cursor, rest) != 0) {
                regfree(&regex);
                free(output);
                return NULL;
            }
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        if (safe_append(output, &out_len, out_cap, cursor,
                        (size_t)match.rm_so) != 0) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        if (cursor != input || match.rm_so > 0) {
            if ((out_len + 1U) >= out_cap) {
                regfree(&regex);
                free(output);
                return NULL;
            }
            output[out_len] = '_';
            out_len++;
        }

        if ((out_len + 1U) >= out_cap) {
            regfree(&regex);
            free(output);
            return NULL;
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