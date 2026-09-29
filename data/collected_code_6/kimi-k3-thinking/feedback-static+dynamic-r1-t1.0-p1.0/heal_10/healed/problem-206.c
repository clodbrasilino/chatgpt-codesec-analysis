#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_ELEMENT_LENGTH (16777216U)
#define DEFAULT_INPUT "DSP IS BEST FOR ALL UTS"

static void free_string_array(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL)
    {
        return;
    }

    for (i = 0U; i < count; i++)
    {
        free(strings[i]);
    }

    free(strings);
}

static size_t bounded_length(const char *s, int *terminated)
{
    size_t len = 0U;

    if (terminated != NULL)
    {
        *terminated = 0;
    }

    if (s == NULL)
    {
        return 0U;
    }

    while (len < MAX_ELEMENT_LENGTH)
    {
        if (s[len] == '\0')
        {
            if (terminated != NULL)
            {
                *terminated = 1;
            }
            return len;
        }
        len++;
    }

    return len;
}

static int bounded_copy(char *dest, size_t dest_capacity, size_t dest_offset, const char *src, size_t src_length)
{
    size_t i;

    if ((dest == NULL) || (src == NULL))
    {
        return -1;
    }

    if (dest_offset > dest_capacity)
    {
        return -1;
    }

    if (src_length > (dest_capacity - dest_offset))
    {
        return -1;
    }

    for (i = 0U; i < src_length; i++)
    {
        dest[dest_offset + i] = src[i];
    }

    return 0;
}

static char **concat_adjacent_elements(const char *const *elements, size_t count, size_t *out_count)
{
    char **result = NULL;
    size_t i;

    if (out_count == NULL)
    {
        return NULL;
    }

    *out_count = 0U;

    if ((elements == NULL) || (count < 2U))
    {
        return NULL;
    }

    if ((count - 1U) > (SIZE_MAX / sizeof(char *)))
    {
        return NULL;
    }

    result = calloc(count - 1U, sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0U; i < (count - 1U); i++)
    {
        const char *left = elements[i];
        const char *right = elements[i + 1U];
        int left_ok = 0;
        int right_ok = 0;
        size_t left_len;
        size_t right_len;
        size_t total_len;
        size_t capacity;

        if ((left == NULL) || (right == NULL))
        {
            free_string_array(result, count - 1U);
            return NULL;
        }

        left_len = bounded_length(left, &left_ok);
        right_len = bounded_length(right, &right_ok);

        if (!left_ok || !right_ok)
        {
            free_string_array(result, count - 1U);
            return NULL;
        }

        if (left_len > (SIZE_MAX - right_len))
        {
            free_string_array(result, count - 1U);
            return NULL;
        }

        total_len = left_len + right_len;

        if (total_len > (SIZE_MAX - 1U))
        {
            free_string_array(result, count - 1U);
            return NULL;
        }

        capacity = total_len + 1U;

        result[i] = malloc(capacity);
        if (result[i] == NULL)
        {
            free_string_array(result, count - 1U);
            return NULL;
        }

        if (bounded_copy(result[i], capacity, 0U, left, left_len) != 0)
        {
            free_string_array(result, count - 1U);
            return NULL;
        }

        if (bounded_copy(result[i], capacity, left_len, right, right_len) != 0)
        {
            free_string_array(result, count - 1U);
            return NULL;
        }

        result[i][total_len] = '\0';
    }

    *out_count = count - 1U;
    return result;
}

static int add_token(char ***tokens, size_t *count, size_t *capacity, char *token)
{
    char **grown = NULL;

    if ((tokens == NULL) || (count == NULL) || (capacity == NULL) || (token == NULL))
    {
        return -1;
    }

    if (*count == *capacity)
    {
        size_t new_capacity = (*capacity == 0U) ? 8U : (*capacity * 2U);

        if ((new_capacity < *capacity) || (new_capacity > (SIZE_MAX / sizeof(**tokens))))
        {
            free(token);
            return -1;
        }

        grown = realloc(*tokens, new_capacity * sizeof(**tokens));
        if (grown == NULL)
        {
            free(token);
            return -1;
        }

        *tokens = grown;
        *capacity = new_capacity;
    }

    (*tokens)[*count] = token;
    *count += 1U;
    return 0;
}

static int split_and_add(const char *text, char ***tokens, size_t *count, size_t *capacity)
{
    const char *cursor = text;

    if ((cursor == NULL) || (tokens == NULL) || (count == NULL) || (capacity == NULL))
    {
        return -1;
    }

    while (*cursor != '\0')
    {
        const char *start = NULL;
        char *token = NULL;
        size_t length = 0U;

        while ((*cursor != '\0') && (isspace((unsigned char)*cursor) != 0))
        {
            cursor++;
        }

        if (*cursor == '\0')
        {
            break;
        }

        start = cursor;

        while ((*cursor != '\0') && (isspace((unsigned char)*cursor) == 0))
        {
            cursor++;
        }

        length = (size_t)(cursor - start);

        if ((length == 0U) || (length >= MAX_ELEMENT_LENGTH))
        {
            return -1;
        }

        token = malloc(length + 1U);
        if (token == NULL)
        {
            return -1;
        }

        if (bounded_copy(token, length + 1U, 0U, start, length) != 0)
        {
            free(token);
            return -1;
        }

        token[length] = '\0';

        if (add_token(tokens, count, capacity, token) != 0)
        {
            return -1;
        }
    }

    return 0;
}

static char *read_stream_contents(FILE *stream)
{
    size_t capacity = 256U;
    size_t length = 0U;
    char *buffer = NULL;

    if (stream == NULL)
    {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL)
    {
        return NULL;
    }

    for (;;)
    {
        size_t available = 0U;
        size_t received = 0U;

        if ((capacity - length) < 2U)
        {
            size_t new_capacity = 0U;
            char *grown = NULL;

            if (capacity > (SIZE_MAX / 2U))
            {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2U;
            grown = realloc(buffer, new_capacity);
            if (grown == NULL)
            {
                free(buffer);
                return NULL;
            }

            buffer = grown;
            capacity = new_capacity;
        }

        available = capacity - length - 1U;
        received = fread(buffer + length, 1U, available, stream);
        length += received;

        if (received < available)
        {
            if (ferror(stream) != 0)
            {
                free(buffer);
                return NULL;
            }
            break;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

int main(int argc, char **argv)
{
    static const char default_input[] = DEFAULT_INPUT;
    char **tokens = NULL;
    size_t token_count = 0U;
    size_t token_capacity = 0U;
    int exit_code = EXIT_FAILURE;

    if (argc > 1)
    {
        int arg_index;

        for (arg_index = 1; arg_index < argc; arg_index++)
        {
            if (split_and_add(argv[arg_index], &tokens, &token_count, &token_capacity) != 0)
            {
                free_string_array(tokens, token_count);
                return EXIT_FAILURE;
            }
        }
    }
    else
    {
        char *input = read_stream_contents(stdin);

        if (input != NULL)
        {
            if (split_and_add(input, &tokens, &token_count, &token_capacity) != 0)
            {
                free(input);
                free_string_array(tokens, token_count);
                return EXIT_FAILURE;
            }
            free(input);
        }
    }

    if (token_count == 0U)
    {
        if (split_and_add(default_input, &tokens, &token_count, &token_capacity) != 0)
        {
            free_string_array(tokens, token_count);
            return EXIT_FAILURE;
        }
    }

    if (token_count >= 2U)
    {
        char **elements = NULL;
        char **result = NULL;
        size_t result_count = 0U;
        size_t i = 0U;

        elements = calloc(token_count, sizeof(*elements));
        if (elements == NULL)
        {
            free_string_array(tokens, token_count);
            return EXIT_FAILURE;
        }

        for (i = 0U; i < token_count; i++)
        {
            int terminated = 0;
            int needs_space = 0;
            size_t length = 0U;
            size_t total = 0U;

            length = bounded_length(tokens[i], &terminated);
            if (!terminated)
            {
                free_string_array(elements, token_count);
                free_string_array(tokens, token_count);
                return EXIT_FAILURE;
            }

            needs_space = ((i + 1U) < token_count) ? 1 : 0;

            if (length > (SIZE_MAX - 2U))
            {
                free_string_array(elements, token_count);
                free_string_array(tokens, token_count);
                return EXIT_FAILURE;
            }

            total = length + ((needs_space != 0) ? 1U : 0U);

            elements[i] = malloc(total + 1U);
            if (elements[i] == NULL)
            {
                free_string_array(elements, token_count);
                free_string_array(tokens, token_count);
                return EXIT_FAILURE;
            }

            if (bounded_copy(elements[i], total + 1U, 0U, tokens[i], length) != 0)
            {
                free_string_array(elements, token_count);
                free_string_array(tokens, token_count);
                return EXIT_FAILURE;
            }

            if (needs_space != 0)
            {
                elements[i][length] = ' ';
            }

            elements[i][total] = '\0';
        }

        result = concat_adjacent_elements((const char *const *)elements, token_count, &result_count);
        if (result == NULL)
        {
            fprintf(stderr, "Error: failed to concatenate adjacent elements.\n");
        }
        else
        {
            for (i = 0U; i < result_count; i++)
            {
                if (printf("%s\n", result[i]) < 0)
                {
                    free_string_array(result, result_count);
                    free_string_array(elements, token_count);
                    free_string_array(tokens, token_count);
                    return EXIT_FAILURE;
                }
            }

            free_string_array(result, result_count);
            exit_code = EXIT_SUCCESS;
        }

        free_string_array(elements, token_count);
    }
    else
    {
        exit_code = EXIT_SUCCESS;
    }

    free_string_array(tokens, token_count);
    return exit_code;
}