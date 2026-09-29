#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_multiple_spaces(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t output_len = 0;
    int ret;

    if (input == NULL || output == NULL || output_size == 0)
    {
        return -1;
    }

    ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0)
    {
        return -1;
    }

    cursor = input;
    output[0] = '\0';

    while (*cursor != '\0')
    {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH)
        {
            break;
        }
        else if (ret != 0)
        {
            regfree(&regex);
            return -1;
        }

        size_t prefix_len = (size_t)match.rm_so;
        if (output_len + prefix_len + 2 > output_size)
        {
            regfree(&regex);
            return -1;
        }

        if (prefix_len > 0)
        {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + output_len, cursor, prefix_len);
            output_len += prefix_len;
        }
        output[output_len++] = ' ';
        output[output_len] = '\0';

        cursor += match.rm_eo;
    }

    size_t max_remaining = output_size - output_len - 1;
    size_t remaining = strnlen(cursor, max_remaining);
    if (remaining == max_remaining && cursor[remaining] != '\0')
    {
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + output_len, cursor, remaining + 1);
    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "This   is    a   test      string.";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    size_t output_size = input_len + 1;
    char *output = malloc(output_size);

    if (output == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (remove_multiple_spaces(input, output, output_size) == 0)
    {
        printf("Original: %s\n", input);
        printf("Modified: %s\n", output);
    }
    else
    {
        fprintf(stderr, "Error processing string\n");
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}