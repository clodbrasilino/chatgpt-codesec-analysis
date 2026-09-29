#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

char *remove_non_alnum(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_len;
    size_t result_pos;
    size_t result_cap;
    size_t offset;
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

    ret = regcomp(&regex, "[^a-zA-Z0-9]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    result_pos = 0;
    offset = 0;

    while (offset < input_len) {
        ret = regexec(&regex, input + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = input_len - offset;
            if (remaining >= result_cap - result_pos) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_pos, input + offset, remaining);
            result_pos += remaining;
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if (match.rm_so > 0) {
            size_t chunk = (size_t)match.rm_so;
            if (chunk > input_len - offset || chunk >= result_cap - result_pos) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_pos, input + offset, chunk);
            result_pos += chunk;
        }
        if (match.rm_eo <= 0 || (size_t)match.rm_eo > input_len - offset) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        offset += (size_t)match.rm_eo;
    }

    if (result_pos >= result_cap) {
        regfree(&regex);
        free(result);
        return NULL;
    }

    result[result_pos] = '\0';

    regfree(&regex);

    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "Hello, World! 123",
        "a@b#c$d%e^1&2*3",
        "!!!???...",
        "AlreadyClean123"
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *cleaned = remove_non_alnum(test_strings[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Failed to process string: %s\n", test_strings[i]);
            return EXIT_FAILURE;
        }
        if (printf("Original: %s\nCleaned:  %s\n\n", test_strings[i], cleaned) < 0) {
            free(cleaned);
            return EXIT_FAILURE;
        }
        free(cleaned);
    }

    return EXIT_SUCCESS;
}