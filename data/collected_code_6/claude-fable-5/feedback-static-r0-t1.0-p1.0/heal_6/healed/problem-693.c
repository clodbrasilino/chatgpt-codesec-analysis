#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096U

static int remove_multiple_spaces(const char *input, char *output, size_t output_size);

static int remove_multiple_spaces(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t out_pos = 0U;
    size_t remaining;
    size_t input_len;
    int ret;

    if ((input == NULL) || (output == NULL) || (output_size == 0U)) {
        return -1;
    }

    output[0] = '\0';

    input_len = strnlen(input, MAX_INPUT_LEN + 1U);
    if (input_len > MAX_INPUT_LEN) {
        return -1;
    }

    ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = input;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t prefix_len;
        size_t space_left;

        if ((match.rm_so < 0) || (match.rm_eo <= match.rm_so)) {
            regfree(&regex);
            output[0] = '\0';
            return -1;
        }

        prefix_len = (size_t)match.rm_so;

        if (out_pos >= (output_size - 1U)) {
            regfree(&regex);
            output[0] = '\0';
            return -1;
        }

        space_left = output_size - 1U - out_pos;

        if (prefix_len >= space_left) {
            regfree(&regex);
            output[0] = '\0';
            return -1;
        }

        memcpy(&output[out_pos], cursor, prefix_len);
        out_pos += prefix_len;
        output[out_pos] = ' ';
        out_pos++;

        cursor += match.rm_eo;
    }

    if (out_pos >= output_size) {
        regfree(&regex);
        output[0] = '\0';
        return -1;
    }

    remaining = strnlen(cursor, MAX_INPUT_LEN);

    if (remaining > (output_size - 1U - out_pos)) {
        regfree(&regex);
        output[0] = '\0';
        return -1;
    }

    memcpy(&output[out_pos], cursor, remaining);
    out_pos += remaining;
    output[out_pos] = '\0';

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *test = "This   is  a    string   with  multiple     spaces.";
    char result[256] = {0};

    if (remove_multiple_spaces(test, result, sizeof(result)) != 0) {
        (void)fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", test) < 0) {
        return EXIT_FAILURE;
    }

    if (printf("Cleaned:  %s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}