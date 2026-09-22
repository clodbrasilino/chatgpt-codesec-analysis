#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LENGTH (1024u * 1024u)

char *remove_lowercase_substrings(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result = NULL;
    char *work = NULL;
    size_t result_len = 0;
    size_t result_cap;
    size_t work_cap;
    size_t input_len;
    size_t pos = 0;
    size_t copy_len;
    int status;
    int regex_compiled = 0;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LENGTH);
    if (input_len == SIZE_MAX) {
        return NULL;
    }

    work_cap = input_len + 1;
    result_cap = input_len + 1;

    work = malloc(work_cap);
    if (work == NULL) {
        return NULL;
    }
    memcpy(work, input, input_len);
    work[input_len] = '\0';

    status = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (status != 0) {
        goto fail;
    }
    regex_compiled = 1;

    result = malloc(result_cap);
    if (result == NULL) {
        goto fail;
    }

    while (pos < input_len) {
        status = regexec(&regex, work + pos, 1, &match, 0);
        if (status == REG_NOMATCH) {
            break;
        }
        if (status != 0) {
            goto fail;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so ||
            (size_t)match.rm_eo > input_len - pos) {
            goto fail;
        }

        if (match.rm_eo == 0) {
            break;
        }

        copy_len = (size_t)match.rm_so;
        if (copy_len > input_len - pos ||
            result_len >= result_cap ||
            copy_len >= result_cap - result_len) {
            goto fail;
        }
        memcpy(result + result_len, work + pos, copy_len);
        result_len += copy_len;
        pos += (size_t)match.rm_eo;
    }

    if (pos < input_len) {
        copy_len = input_len - pos;
        if (result_len >= result_cap ||
            copy_len >= result_cap - result_len) {
            goto fail;
        }
        memcpy(result + result_len, work + pos, copy_len);
        result_len += copy_len;
    }

    if (result_len >= result_cap) {
        goto fail;
    }
    result[result_len] = '\0';

    regfree(&regex);
    free(work);
    return result;

fail:
    if (regex_compiled) {
        regfree(&regex);
    }
    free(work);
    free(result);
    return NULL;
}

int main(void)
{
    const char *test_strings[] = {
        "HELLOworldTHISisTESTingSTRING",
        "alllowercase",
        "ALLUPPERCASE",
        "Mix3dW0rdsHere",
        ""
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        char *result = remove_lowercase_substrings(test_strings[i]);
        if (result == NULL) {
            fprintf(stderr, "Failed to process string at index %zu\n", i);
            return EXIT_FAILURE;
        }

        printf("Original: \"%s\"\n", test_strings[i]);
        printf("Modified: \"%s\"\n\n", result);

        free(result);
    }

    return EXIT_SUCCESS;
}