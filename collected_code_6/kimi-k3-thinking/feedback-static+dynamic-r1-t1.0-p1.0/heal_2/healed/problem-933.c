#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <regex.h>
#include <sys/types.h>

#define MAX_INPUT_LENGTH 4096

char *camel_to_snake(const char *input)
{
    regex_t regex;
    regmatch_t match[1];
    char *output;
    size_t input_len;
    size_t offset;
    size_t out_pos;
    int ret;

    if (input == NULL)
    {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LENGTH + 1);
    if (input_len > MAX_INPUT_LENGTH)
    {
        return NULL;
    }

    if (input_len > (SIZE_MAX - 1) / 2)
    {
        return NULL;
    }

    output = malloc(2 * input_len + 1);
    if (output == NULL)
    {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0)
    {
        free(output);
        return NULL;
    }

    offset = 0;
    out_pos = 0;

    while (offset < input_len)
    {
        size_t match_start;
        size_t match_end;

        ret = regexec(&regex, input + offset, 1, match, 0);
        if (ret == REG_NOMATCH)
        {
            break;
        }
        if (ret != 0)
        {
            regfree(&regex);
            free(output);
            return NULL;
        }

        match_start = offset + (size_t)match[0].rm_so;
        match_end = offset + (size_t)match[0].rm_eo;

        while (offset < match_start)
        {
            output[out_pos++] = input[offset++];
        }

        if (match_start != 0)
        {
            output[out_pos++] = '_';
        }
        output[out_pos++] = (char)tolower((unsigned char)input[match_start]);

        offset = match_end;
    }

    while (offset < input_len)
    {
        output[out_pos++] = input[offset++];
    }
    output[out_pos] = '\0';

    regfree(&regex);
    return output;
}

int main(void)
{
    char *input = NULL;
    size_t input_capacity = 0;
    ssize_t input_length;
    char *result;

    input_length = getline(&input, &input_capacity, stdin);
    if (input_length < 0)
    {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    result = camel_to_snake(input);
    if (result == NULL)
    {
        fprintf(stderr, "Conversion failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("%s\n", result);
    free(result);
    free(input);

    return EXIT_SUCCESS;
}