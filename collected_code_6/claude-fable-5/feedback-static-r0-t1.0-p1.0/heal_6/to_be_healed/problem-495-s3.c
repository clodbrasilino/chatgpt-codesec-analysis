#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096
#define RESULT_SIZE 256

static int append_segment(char *output, size_t output_size,
                          size_t *out_len, const char *src, size_t seg_len)
{
    if (output == NULL || out_len == NULL || src == NULL) {
        return -1;
    }
    if (*out_len >= output_size) {
        return -1;
    }
    if (seg_len >= output_size - *out_len) {
        return -1;
    }
    memmove(output + *out_len, src, seg_len);
    *out_len += seg_len;
    return 0;
}

int remove_lowercase(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t out_len = 0;
    const char *cursor;
    size_t input_len;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return -1;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = input;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, MAX_INPUT_LEN);
            if (remaining >= MAX_INPUT_LEN ||
                append_segment(output, output_size, &out_len,
                               cursor, remaining) != 0) {
                regfree(&regex);
                return -1;
            }
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            return -1;
        }
        if (match.rm_so > 0) {
            size_t seg_len = (size_t)match.rm_so;
            if (append_segment(output, output_size, &out_len,
                               cursor, seg_len) != 0) {
                regfree(&regex);
                return -1;
            }
        }
        if (match.rm_eo <= 0) {
            regfree(&regex);
            return -1;
        }
        cursor += match.rm_eo;
    }

    if (out_len >= output_size) {
        regfree(&regex);
        return -1;
    }
    output[out_len] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *test_strings[] = {
        "HelloWorldFooBAR",
        "abcDEFghiJKL",
        "ALLUPPERCASE",
        "alllowercase",
        "Mix3d C4s3 Str1ng"
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[RESULT_SIZE];

    for (i = 0; i < count; i++) {
        memset(result, 0, sizeof(result));
        if (remove_lowercase(test_strings[i], result, sizeof(result)) == 0) {
            printf("Input:  %s\n", test_strings[i]);
            printf("Output: %s\n\n", result);
        } else {
            fprintf(stderr, "Failed to process string: %s\n", test_strings[i]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}