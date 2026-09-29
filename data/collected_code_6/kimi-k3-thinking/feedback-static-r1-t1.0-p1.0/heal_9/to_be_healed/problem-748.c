#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

static int ensure_capacity(char **buffer, size_t *capacity, size_t needed)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL || *buffer == NULL)
    {
        return -1;
    }

    if (needed <= *capacity)
    {
        return 0;
    }

    new_capacity = *capacity;
    while (new_capacity < needed)
    {
        if (new_capacity > SIZE_MAX / 2)
        {
            new_capacity = needed;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity < needed)
    {
        return -1;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL)
    {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int append_bytes(char **buffer, size_t *capacity, size_t *length,
                        const char *data, size_t data_len)
{
    size_t space_left;

    if (buffer == NULL || capacity == NULL || length == NULL ||
        data == NULL || *buffer == NULL)
    {
        return -1;
    }

    if (*length >= SIZE_MAX - 1 || data_len > SIZE_MAX - *length - 1)
    {
        return -1;
    }

    if (ensure_capacity(buffer, capacity, *length + data_len + 1) != 0)
    {
        return -1;
    }

    if (*length >= *capacity)
    {
        return -1;
    }

    space_left = *capacity - *length;

    if (data_len >= space_left)
    {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(*buffer + *length, data, data_len);
    *length += data_len;
    (*buffer)[*length] = '\0';
    return 0;
}

char *insert_spaces_between_capital_words(const char *input)
{
    regex_t regex;
    regmatch_t matches[3];
    const char *pattern = "([[:alnum:]_])([[:upper:]])";
    char *result = NULL;
    size_t capacity;
    size_t length = 0;
    size_t offset = 0;
    size_t input_len;
    size_t remaining;

    if (input == NULL)
    {
        return NULL;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
    {
        return NULL;
    }

    input_len = strnlen(input, ((SIZE_MAX - 1) / 2) + 1);
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
    result[0] = '\0';

    while (regexec(&regex, input + offset, 3, matches, 0) == 0)
    {
        size_t chunk_len;
        size_t advance;

        if (matches[1].rm_so < 0 || matches[1].rm_eo <= 0 ||
            matches[2].rm_so <= 0 || matches[2].rm_eo < 0 ||
            matches[1].rm_eo < matches[1].rm_so ||
            matches[2].rm_so < matches[1].rm_eo)
        {
            free(result);
            regfree(&regex);
            return NULL;
        }

        chunk_len = (size_t)matches[1].rm_eo;
        advance = (size_t)matches[2].rm_so;

        if (offset > input_len ||
            chunk_len > input_len - offset ||
            advance > input_len - offset)
        {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (append_bytes(&result, &capacity, &length,
                         input + offset, chunk_len) != 0)
        {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (append_bytes(&result, &capacity, &length, " ", 1) != 0)
        {
            free(result);
            regfree(&regex);
            return NULL;
        }

        offset += advance;
    }

    if (offset > input_len)
    {
        free(result);
        regfree(&regex);
        return NULL;
    }

    remaining = input_len - offset;

    if (append_bytes(&result, &capacity, &length,
                     input + offset, remaining) != 0)
    {
        free(result);
        regfree(&regex);
        return NULL;
    }

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