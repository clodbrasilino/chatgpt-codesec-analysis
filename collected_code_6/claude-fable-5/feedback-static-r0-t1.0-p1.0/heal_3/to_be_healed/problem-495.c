#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_lowercase(const char *input, char *output, size_t output_size);

static int append_bytes(char *output, size_t output_size, size_t *out_len,
                        const char *src, size_t len)
{
    if (len == 0) {
        return 0;
    }
    if (*out_len >= output_size) {
        return -1;
    }
    if (len >= output_size - *out_len) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + *out_len, src, len);
    *out_len += len;
    return 0;
}

int remove_lowercase(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t out_len = 0;
    int rc;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    output[0] = '\0';

    rc = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (rc != 0) {
        return -1;
    }

    cursor = input;
    while (*cursor != '\0') {
        rc = regexec(&regex, cursor, 1, &match, 0);
        if (rc == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, output_size);
            if (remaining >= output_size ||
                append_bytes(output, output_size, &out_len, cursor, remaining) != 0) {
                regfree(&regex);
                output[0] = '\0';
                return -1;
            }
            break;
        }
        if (rc != 0) {
            regfree(&regex);
            output[0] = '\0';
            return -1;
        }
        if (match.rm_so > 0) {
            size_t prefix_len = (size_t)match.rm_so;
            if (append_bytes(output, output_size, &out_len, cursor, prefix_len) != 0) {
                regfree(&regex);
                output[0] = '\0';
                return -1;
            }
        }
        if (match.rm_eo <= 0) {
            regfree(&regex);
            output[0] = '\0';
            return -1;
        }
        cursor += match.rm_eo;
    }

    if (out_len >= output_size) {
        regfree(&regex);
        output[0] = '\0';
        return -1;
    }

    output[out_len] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    static const char *const test_strings[] = {
        "HelloWORLDfooBAR",
        "abcDEFghiJKL",
        "ALLUPPERCASE",
        "alllowercase",
        "Mix123edCaseWith456numbers"
    };
    const size_t max_input_len = 4096;
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        size_t input_len = strnlen(test_strings[i], max_input_len);
        size_t buf_size;
        char *result;

        if (input_len >= max_input_len) {
            fprintf(stderr, "Input string too long\n");
            return EXIT_FAILURE;
        }

        buf_size = input_len + 1;
        result = malloc(buf_size);
        if (result == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        if (remove_lowercase(test_strings[i], result, buf_size) == 0) {
            printf("Input:  \"%s\"\n", test_strings[i]);
            printf("Output: \"%s\"\n\n", result);
        } else {
            fprintf(stderr, "Failed to process string: %s\n", test_strings[i]);
            free(result);
            return EXIT_FAILURE;
        }
        free(result);
    }

    return EXIT_SUCCESS;
}