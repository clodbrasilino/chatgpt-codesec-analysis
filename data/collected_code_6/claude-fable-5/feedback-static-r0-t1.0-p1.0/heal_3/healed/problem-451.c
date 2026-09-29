#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

static int append_bytes(char *output, size_t output_size, size_t *out_pos,
                        const char *src, size_t len)
{
    if (output == NULL || out_pos == NULL || src == NULL) {
        return -1;
    }
    if (len == 0) {
        return 0;
    }
    if (output_size == 0 || *out_pos >= output_size ||
        len > output_size - *out_pos - 1) {
        return -1;
    }
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
    size_t remaining_len;
    const char *cursor;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return -1;
    }

    ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = input;
    remaining_len = input_len;

    while (remaining_len > 0 && *cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            if (append_bytes(output, output_size, &out_pos, cursor,
                             remaining_len) != 0) {
                regfree(&regex);
                return -1;
            }
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so ||
            (size_t)match.rm_eo > remaining_len) {
            regfree(&regex);
            return -1;
        }

        if ((size_t)match.rm_so > 0) {
            if (append_bytes(output, output_size, &out_pos, cursor,
                             (size_t)match.rm_so) != 0) {
                regfree(&regex);
                return -1;
            }
        }

        cursor += (size_t)match.rm_eo;
        remaining_len -= (size_t)match.rm_eo;
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
    static const char test[] = "  Hello,   World!\tThis is\na test string.  ";
    char result[MAX_INPUT_LEN];

    memset(result, 0, sizeof(result));

    if (sizeof(test) > sizeof(result)) {
        fprintf(stderr, "Input too large for output buffer\n");
        return EXIT_FAILURE;
    }

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