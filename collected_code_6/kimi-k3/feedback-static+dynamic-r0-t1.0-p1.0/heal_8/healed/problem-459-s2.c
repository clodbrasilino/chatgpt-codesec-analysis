#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>
#include <stdbool.h>

static char *remove_uppercase_substrings(const char *input, size_t input_len)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char *result;
    size_t result_len;
    size_t remaining;
    size_t copy_len;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    if (input_len == SIZE_MAX) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = (char *)malloc(input_len + 1U);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    result_len = 0U;
    remaining = input_len;

    while (remaining > 0U) {
        ret = regexec(&regex, cursor, 1U, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_eo < match.rm_so) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if ((size_t)match.rm_so > remaining || (size_t)match.rm_eo > remaining) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so > 0) {
            copy_len = (size_t)match.rm_so;
            if (copy_len > input_len || result_len > input_len - copy_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            if (result_len + copy_len > input_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            if (result_len + copy_len > input_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
        }

        cursor += match.rm_eo;
        remaining -= (size_t)match.rm_eo;
    }

    if (remaining > 0U) {
        if (remaining > input_len || result_len > input_len - remaining) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (result_len + remaining > input_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + result_len, cursor, remaining);
        result_len += remaining;
    }
    result[result_len] = '\0';

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *input = "HelloWORLDThisISAtestSTRINGok";
    size_t input_len;
    char *output;

    input_len = strnlen(input, 1024U);
    output = remove_uppercase_substrings(input, input_len);

    if (output == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", output);
    free(output);
    return EXIT_SUCCESS;
}