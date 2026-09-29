#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define RESULT_BUFFER_SIZE 256U

int remove_multiple_spaces(const char *input, char *output, size_t output_size);

static int append_bytes(char *output, size_t output_size, size_t *out_pos,
                        const char *src, size_t len)
{
    size_t space_left;

    if ((output == NULL) || (out_pos == NULL) || (src == NULL)) {
        return -1;
    }

    if (*out_pos >= output_size) {
        return -1;
    }

    space_left = output_size - *out_pos;

    if (len >= space_left) {
        return -1;
    }

    if (len > 0U) {
        memcpy(&output[*out_pos], src, len);
        *out_pos += len;
    }

    return 0;
}

int remove_multiple_spaces(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t out_pos = 0U;
    int ret;

    if ((input == NULL) || (output == NULL) || (output_size == 0U)) {
        return -1;
    }

    output[0] = '\0';

    ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = input;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t prefix_len;

        if ((match.rm_so < 0) || (match.rm_eo <= match.rm_so)) {
            regfree(&regex);
            return -1;
        }

        prefix_len = (size_t)match.rm_so;

        if (append_bytes(output, output_size, &out_pos, cursor, prefix_len) != 0) {
            regfree(&regex);
            return -1;
        }

        if ((out_pos + 1U) >= output_size) {
            regfree(&regex);
            return -1;
        }

        output[out_pos] = ' ';
        out_pos++;

        cursor += (size_t)match.rm_eo;
    }

    {
        size_t remaining;

        if (out_pos >= output_size) {
            regfree(&regex);
            return -1;
        }

        remaining = strnlen(cursor, output_size);

        if (remaining >= output_size) {
            regfree(&regex);
            return -1;
        }

        if (append_bytes(output, output_size, &out_pos, cursor, remaining) != 0) {
            regfree(&regex);
            return -1;
        }

        if (out_pos >= output_size) {
            regfree(&regex);
            return -1;
        }

        output[out_pos] = '\0';
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    static const char test[] = "This   is  a    string   with  multiple     spaces.";
    char result[RESULT_BUFFER_SIZE];

    memset(result, 0, sizeof(result));

    if (strnlen(test, sizeof(result)) >= sizeof(result)) {
        (void)fprintf(stderr, "Input too long for buffer.\n");
        return EXIT_FAILURE;
    }

    if (remove_multiple_spaces(test, result, sizeof(result)) != 0) {
        (void)fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    result[sizeof(result) - 1U] = '\0';

    if (printf("Original: %s\n", test) < 0) {
        return EXIT_FAILURE;
    }

    if (printf("Cleaned:  %s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}