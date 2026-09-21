#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_multiple_spaces(const char *input);

char *remove_multiple_spaces(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *output;
    const char *cursor;
    size_t input_len;
    size_t out_len;
    size_t remainder_len;
    size_t output_size;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    input_len = strnlen(input, (size_t)-1 / 2U);

    if (input_len >= ((size_t)-1 / 2U)) {
        regfree(&regex);
        return NULL;
    }

    output_size = input_len + 1U;

    output = malloc(output_size);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    out_len = 0U;
    cursor = input;

    while ((ret = regexec(&regex, cursor, 1U, &match, 0)) == 0) {
        const size_t prefix_len = (size_t)match.rm_so;

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        if (prefix_len > (output_size - 1U) ||
            out_len > ((output_size - 1U) - prefix_len)) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        memcpy(output + out_len, cursor, prefix_len);
        out_len += prefix_len;
        output[out_len] = ' ';
        out_len += 1U;
        cursor += match.rm_eo;
    }

    if (ret != REG_NOMATCH) {
        free(output);
        regfree(&regex);
        return NULL;
    }

    if ((size_t)(cursor - input) > input_len) {
        free(output);
        regfree(&regex);
        return NULL;
    }

    remainder_len = strnlen(cursor, input_len - (size_t)(cursor - input));

    if (remainder_len > (output_size - 1U) ||
        out_len > ((output_size - 1U) - remainder_len)) {
        free(output);
        regfree(&regex);
        return NULL;
    }

    memcpy(output + out_len, cursor, remainder_len);
    out_len += remainder_len;
    output[out_len] = '\0';

    regfree(&regex);
    return output;
}

int main(void)
{
    const char *test = "This   is  a    string   with     multiple spaces.";
    char *result;

    result = remove_multiple_spaces(test);
    if (result == NULL) {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", test) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    if (printf("Cleaned:  %s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}