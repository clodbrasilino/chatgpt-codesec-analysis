#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

char *remove_uppercase(const char *input);

char *remove_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_len;
    size_t result_len;
    size_t result_cap;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result_cap = input_len + 1;
    result = malloc(result_cap);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    result_len = 0;
    cursor = input;

    while (*cursor != '\0') {
        size_t consumed = (size_t)(cursor - input);

        if (consumed > input_len) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, input_len - consumed);
            if (result_len >= result_cap ||
                remaining >= result_cap - result_len) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            if (remaining > 0 &&
                result_len + remaining < result_cap) {
                memcpy(result + result_len, cursor, remaining);
                result_len += remaining;
            }
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if ((size_t)match.rm_so > input_len - consumed ||
            (size_t)match.rm_eo > input_len - consumed) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if (result_len >= result_cap ||
            (size_t)match.rm_so >= result_cap - result_len) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if ((size_t)match.rm_so > 0 &&
            result_len + (size_t)match.rm_so < result_cap) {
            memcpy(result + result_len, cursor, (size_t)match.rm_so);
            result_len += (size_t)match.rm_so;
        }
        cursor += match.rm_eo;
    }

    if (result_len >= result_cap) {
        regfree(&regex);
        free(result);
        return NULL;
    }

    result[result_len] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "helloWORLDthisIS a TEST string",
        "ALLUPPERCASE",
        "nolowercasehere",
        "MixedCASEString"
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *cleaned = remove_uppercase(test_strings[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Failed to process string: %s\n", test_strings[i]);
            return EXIT_FAILURE;
        }
        if (printf("Original: \"%s\" -> Result: \"%s\"\n", test_strings[i], cleaned) < 0) {
            free(cleaned);
            return EXIT_FAILURE;
        }
        free(cleaned);
    }

    return EXIT_SUCCESS;
}