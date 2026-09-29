#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 4096
#define RESULT_BUFFER_SIZE 256

static int append_bytes(char *output, size_t output_size, size_t *out_pos,
                        const char *src, size_t len)
{
    if (output == NULL || out_pos == NULL || src == NULL) {
        return -1;
    }
    if (len == 0) {
        return 0;
    }
    if (len >= output_size) {
        return -1;
    }
    if (*out_pos > output_size - 1 - len) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + *out_pos, src, len);
    *out_pos += len;
    return 0;
}

int remove_whitespace(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t out_pos = 0;
    size_t input_len;
    const char *cursor;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    input_len = strnlen(input, MAX_INPUT_LENGTH);
    if (input_len >= MAX_INPUT_LENGTH) {
        return -1;
    }

    ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = input;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t consumed = (size_t)(cursor - input);
            size_t remaining;
            if (consumed > input_len) {
                regfree(&regex);
                return -1;
            }
            remaining = strnlen(cursor, input_len - consumed);
            if (append_bytes(output, output_size, &out_pos, cursor, remaining) != 0) {
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
            size_t chunk = (size_t)match.rm_so;
            if (append_bytes(output, output_size, &out_pos, cursor, chunk) != 0) {
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

    if (out_pos >= output_size) {
        regfree(&regex);
        return -1;
    }

    output[out_pos] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *test = "  Hello,   World!\tThis is\na test string.  ";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[RESULT_BUFFER_SIZE];

    memset(result, 0, sizeof(result));

    if (remove_whitespace(test, result, sizeof(result)) != 0) {
        fprintf(stderr, "Failed to remove whitespace\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: \"%s\"\n", test) < 0) {
        return EXIT_FAILURE;
    }
    if (printf("Result:   \"%s\"\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}