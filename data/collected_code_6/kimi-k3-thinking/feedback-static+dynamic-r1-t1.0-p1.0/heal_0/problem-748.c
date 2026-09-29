#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

char *insert_spaces_between_capital_words(const char *input)
{
    regex_t regex;
    regmatch_t matches[3];
    const char *pattern = "([[:alnum:]_])([[:upper:]])";
    char *result;
    size_t capacity;
    size_t length = 0;
    size_t offset = 0;
    size_t input_len;

    if (input == NULL)
    {
        return NULL;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
    {
        return NULL;
    }

    input_len = strlen(input);
    if (input_len > (SIZE_MAX - 1) / 2)
    {
        regfree(&regex);
        return NULL;
    }

    capacity = input_len * 2 + 1;
    result = malloc(capacity);
    if (result == NULL)
    {
        regfree(&regex);
        return NULL;
    }

    while (regexec(&regex, input + offset, 3, matches, 0) == 0)
    {
        size_t chunk_len = (size_t)matches[1].rm_eo;

        if (length + chunk_len + 2 > capacity)
        {
            char *resized = realloc(result, capacity * 2);
            if (resized == NULL)
            {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = resized;
            capacity *= 2;
        }

        memcpy(result + length, input + offset, chunk_len);
        length += chunk_len;
        result[length] = ' ';
        length++;
        offset += (size_t)matches[2].rm_so;
    }

    strcpy(result + length, input + offset);

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *input = "HelloWorldThisIsATestString";
    char *output = insert_spaces_between_capital_words(input);

    if (output == NULL)
    {
        fprintf(stderr, "Failed to process the input string\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);
    return EXIT_SUCCESS;
}