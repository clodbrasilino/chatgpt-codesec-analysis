#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 4096

char *remove_lowercase_substrings(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result = NULL;
    char *bounded_input = NULL;
    size_t result_len = 0;
    size_t input_len;
    size_t pos = 0;
    int status;

    if (input == NULL) {
        return NULL;
    }

    status = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LENGTH);

    bounded_input = malloc(input_len + 1);
    if (bounded_input == NULL) {
        regfree(&regex);
        return NULL;
    }
    memcpy(bounded_input, input, input_len);
    bounded_input[input_len] = '\0';

    result = malloc(input_len + 1);
    if (result == NULL) {
        free(bounded_input);
        regfree(&regex);
        return NULL;
    }

    while (pos < input_len) {
        size_t copy_len;

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

        copy_len = (size_t)match.rm_so;
        if (copy_len > input_len - result_len) {
            free(result);
            free(bounded_input);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + result_len, bounded_input + pos, copy_len);
        result_len += copy_len;
        pos += (size_t)match.rm_eo;
    }

    if (pos < input_len) {
        size_t copy_len = input_len - pos;
        if (copy_len > input_len - result_len) {
            free(result);
            free(bounded_input);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + result_len, bounded_input + pos, copy_len);
        result_len += copy_len;
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