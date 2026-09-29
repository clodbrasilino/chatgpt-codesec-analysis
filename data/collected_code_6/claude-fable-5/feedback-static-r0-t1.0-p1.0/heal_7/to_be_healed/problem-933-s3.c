#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096U

char *camel_to_snake(const char *input);

static int safe_copy(char *dest, size_t dest_capacity, size_t dest_len,
                     const char *src, size_t src_len)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (dest_capacity == 0U) {
        return -1;
    }
    if (src_len > (dest_capacity - 1U)) {
        return -1;
    }
    if (dest_len > ((dest_capacity - 1U) - src_len)) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest + dest_len, src, src_len);
    return 0;
}

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

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

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
            if (safe_copy(output, out_capacity, out_len,
                          input + offset, remaining) != 0) {
                regfree(&regex);
                free(output);
                return NULL;
            }
            out_len += remaining;
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo <= 0) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        if ((size_t)match.rm_so > (input_len - offset)) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        if ((out_len + (size_t)match.rm_so + 2U) >= out_capacity) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        if (safe_copy(output, out_capacity, out_len,
                      input + offset, (size_t)match.rm_so) != 0) {
            regfree(&regex);
            free(output);
            return NULL;
        }
        out_len += (size_t)match.rm_so;

        if ((offset + (size_t)match.rm_so) > 0U) {
            if (out_len >= (out_capacity - 1U)) {
                regfree(&regex);
                free(output);
                return NULL;
            }
            output[out_len] = '_';
            out_len++;
        }

        if (out_len >= (out_capacity - 1U)) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        output[out_len] = (char)tolower((unsigned char)input[offset + (size_t)match.rm_so]);
        out_len++;

        offset += (size_t)match.rm_eo;
    }

    if (out_len >= out_capacity) {
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