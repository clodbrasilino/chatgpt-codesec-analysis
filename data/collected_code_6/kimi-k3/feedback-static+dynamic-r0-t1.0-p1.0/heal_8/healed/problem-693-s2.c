#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_multiple_spaces(const char *input, size_t input_len, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    size_t cursor_pos = 0;
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

    output[0] = '\0';

    while (cursor_pos < input_len)
    {
        ret = regexec(&regex, input + cursor_pos, 1, &match, 0);
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
            memcpy(output + output_len, input + cursor_pos, prefix_len);
            output_len += prefix_len;
        }

        output[output_len++] = ' ';
        output[output_len] = '\0';

        cursor_pos += (size_t)match.rm_eo;
    }

    size_t remaining = input_len - cursor_pos;

    if (output_len + remaining + 1 > output_size)
    {
        regfree(&regex);
        return -1;
    }

    if (remaining > 0)
    {
        memcpy(output + output_len, input + cursor_pos, remaining);
    }
    output[output_len + remaining] = '\0';

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "This   is    a   test      string.";
    size_t input_len = strnlen(input, 1024);
    size_t output_size = input_len + 1;
    char *output = malloc(output_size);

    if (output == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (remove_multiple_spaces(input, input_len, output, output_size) == 0)
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