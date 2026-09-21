#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 4096

static int checked_copy(char *dest, size_t dest_capacity, size_t dest_offset, const char *src, size_t copy_len)
{
    size_t i;

    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (dest_capacity == 0 || dest_offset >= dest_capacity) {
        return -1;
    }
    if (copy_len > dest_capacity - dest_offset - 1) {
        return -1;
    }
    for (i = 0; i < copy_len; i++) {
        dest[dest_offset + i] = src[i];
    }
    dest[dest_offset + copy_len] = '\0';
    return 0;
}

char *remove_lowercase_substrings(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result = NULL;
    char *bounded_input = NULL;
    size_t result_len = 0;
    size_t result_capacity;
    size_t input_len;
    size_t pos = 0;
    int status;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LENGTH + 1);
    if (input_len > MAX_INPUT_LENGTH) {
        return NULL;
    }

    status = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    bounded_input = malloc(input_len + 1);
    if (bounded_input == NULL) {
        regfree(&regex);
        return NULL;
    }

    if (checked_copy(bounded_input, input_len + 1, 0, input, input_len) != 0) {
        free(bounded_input);
        regfree(&regex);
        return NULL;
    }
    bounded_input[input_len] = '\0';

    result_capacity = input_len + 1;
    result = malloc(result_capacity);
    if (result == NULL) {
        free(bounded_input);
        regfree(&regex);
        return NULL;
    }

    while (pos < input_len) {
        size_t copy_len;
        size_t remaining;

        status = regexec(&regex, bounded_input + pos, 1, &match, 0);
        if (status == REG_NOMATCH) {
            break;
        }
        if (status != 0) {
            free(result);
            free(bounded_input);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo <= 0 || match.rm_eo < match.rm_so) {
            free(result);
            free(bounded_input);
            regfree(&regex);
            return NULL;
        }

        remaining = input_len - pos;
        if ((size_t)match.rm_so > remaining || (size_t)match.rm_eo > remaining) {
            free(result);
            free(bounded_input);
            regfree(&regex);
            return NULL;
        }

        copy_len = (size_t)match.rm_so;
        if (copy_len > 0) {
            if (checked_copy(result, result_capacity, result_len, bounded_input + pos, copy_len) != 0) {
                free(result);
                free(bounded_input);
                regfree(&regex);
                return NULL;
            }
            result_len += copy_len;
        }
        pos += (size_t)match.rm_eo;
    }

    if (pos < input_len) {
        size_t copy_len = input_len - pos;

        if (checked_copy(result, result_capacity, result_len, bounded_input + pos, copy_len) != 0) {
            free(result);
            free(bounded_input);
            regfree(&regex);
            return NULL;
        }
        result_len += copy_len;
    }

    if (result_len >= result_capacity) {
        free(result);
        free(bounded_input);
        regfree(&regex);
        return NULL;
    }
    result[result_len] = '\0';

    free(bounded_input);
    regfree(&regex);

    return result;
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