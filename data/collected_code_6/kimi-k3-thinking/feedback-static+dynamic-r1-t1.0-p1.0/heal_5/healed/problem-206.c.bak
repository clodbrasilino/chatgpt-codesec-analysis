#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

static char **concat_adjacent_elements(const char *const *elements, size_t count, size_t *out_count)
{
    char **result;
    size_t i;

    if (out_count == NULL)
    {
        return NULL;
    }
    *out_count = 0U;

    if (elements == NULL || count < 2U)
    {
        return NULL;
    }

    for (i = 0U; i < count; i++)
    {
        if (elements[i] == NULL)
        {
            return NULL;
        }
    }

    if (count - 1U > SIZE_MAX / sizeof(*result))
    {
        return NULL;
    }

    result = malloc((count - 1U) * sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0U; i < count - 1U; i++)
    {
        size_t left_len = strlen(elements[i]);
        size_t right_len = strlen(elements[i + 1U]);

        if (left_len > SIZE_MAX - right_len - 1U)
        {
            free_string_array(result, i);
            return NULL;
        }

        result[i] = malloc(left_len + right_len + 1U);
        if (result[i] == NULL)
        {
            free_string_array(result, i);
            return NULL;
        }

        memcpy(result[i], elements[i], left_len);
        memcpy(result[i] + left_len, elements[i + 1U], right_len);
        result[i][left_len + right_len] = '\0';
    }

    *out_count = count - 1U;
    return result;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 64U;
    size_t length = 0U;
    char *buffer;
    int ch;

    buffer = malloc(capacity);
    if (buffer == NULL)
    {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n')
    {
        if (length + 1U >= capacity)
        {
            size_t new_capacity = capacity * 2U;
            char *new_buffer;

            if (new_capacity <= capacity)
            {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL)
            {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length] = (char)ch;
        length++;
    }

    if (ch == EOF && length == 0U)
    {
        free(buffer);
        return NULL;
    }

    if (length > 0U && buffer[length - 1U] == '\r')
    {
        length--;
    }

    buffer[length] = '\0';
    return buffer;
}

static char **read_all_lines(FILE *stream, size_t *out_count)
{
    char **lines = NULL;
    size_t count = 0U;
    size_t capacity = 0U;
    char *line;

    if (out_count == NULL)
    {
        return NULL;
    }
    *out_count = 0U;

    while ((line = read_line(stream)) != NULL)
    {
        if (count == capacity)
        {
            size_t new_capacity = (capacity == 0U) ? 8U : capacity * 2U;
            char **new_lines;

            if (new_capacity <= capacity || new_capacity > SIZE_MAX / sizeof(*new_lines))
            {
                free(line);
                free_string_array(lines, count);
                return NULL;
            }

            new_lines = realloc(lines, new_capacity * sizeof(*new_lines));
            if (new_lines == NULL)
            {
                free(line);
                free_string_array(lines, count);
                return NULL;
            }

            lines = new_lines;
            capacity = new_capacity;
        }

        lines[count] = line;
        count++;
    }

    *out_count = count;
    return lines;
}

static int append_token(char ***tokens, size_t *count, size_t *capacity, const char *start, size_t length, int add_space)
{
    char *token;
    size_t size;

    if (tokens == NULL || count == NULL || capacity == NULL || start == NULL)
    {
        return 0;
    }

    if (*count == *capacity)
    {
        size_t new_capacity = (*capacity == 0U) ? 8U : (*capacity * 2U);
        char **new_tokens;

        if (new_capacity <= *capacity || new_capacity > SIZE_MAX / sizeof(*new_tokens))
        {
            return 0;
        }

        new_tokens = realloc(*tokens, new_capacity * sizeof(*new_tokens));
        if (new_tokens == NULL)
        {
            return 0;
        }

        *tokens = new_tokens;
        *capacity = new_capacity;
    }

    size = length + (add_space ? 1U : 0U) + 1U;
    token = malloc(size);
    if (token == NULL)
    {
        return 0;
    }

    memcpy(token, start, length);
    if (add_space)
    {
        token[length] = ' ';
    }
    token[size - 1U] = '\0';

    (*tokens)[*count] = token;
    *count += 1U;
    return 1;
}

static int tokenize_string(const char *text, char ***tokens, size_t *count, size_t *capacity)
{
    size_t i = 0U;

    if (text == NULL)
    {
        return 1;
    }

    while (text[i] != '\0')
    {
        size_t start;

        while (text[i] == ' ')
        {
            i++;
        }
        if (text[i] == '\0')
        {
            break;
        }

        start = i;
        while (text[i] != '\0' && text[i] != ' ')
        {
            i++;
        }

        if (!append_token(tokens, count, capacity, text + start, i - start, text[i] == ' '))
        {
            return 0;
        }
    }

    return 1;
}

static int is_count_token(const char *text, size_t expected)
{
    size_t value = 0U;
    size_t length;
    size_t i;

    if (text == NULL)
    {
        return 0;
    }

    length = strlen(text);
    while (length > 0U && text[length - 1U] == ' ')
    {
        length--;
    }
    if (length == 0U)
    {
        return 0;
    }

    for (i = 0U; i < length; i++)
    {
        if (text[i] < '0' || text[i] > '9')
        {
            return 0;
        }
        if (value > (SIZE_MAX - 9U) / 10U)
        {
            return 0;
        }
        value = value * 10U + (size_t)(text[i] - '0');
    }

    return value == expected;
}

int main(int argc, const char *argv[])
{
    char **owned = NULL;
    char **words = NULL;
    char **result;
    size_t line_count = 0U;
    size_t count = 0U;
    size_t capacity = 0U;
    size_t result_count = 0U;
    size_t i;
    size_t length;

    if (argc >= 2)
    {
        char *sentence;
        size_t position;

        length = 0U;
        for (i = 1U; i < (size_t)argc; i++)
        {
            size_t arg_length = strlen(argv[i]);
            if (length > SIZE_MAX - arg_length - 1U)
            {
                return EXIT_FAILURE;
            }
            length += arg_length + 1U;
        }

        sentence = malloc(length + 1U);
        if (sentence == NULL)
        {
            return EXIT_FAILURE;
        }

        position = 0U;
        for (i = 1U; i < (size_t)argc; i++)
        {
            size_t arg_length = strlen(argv[i]);
            memcpy(sentence + position, argv[i], arg_length);
            position += arg_length;
            sentence[position] = ' ';
            position++;
        }
        sentence[position] = '\0';

        if (!tokenize_string(sentence, &words, &count, &capacity))
        {
            free(sentence);
            free_string_array(words, count);
            return EXIT_FAILURE;
        }
        free(sentence);
    }
    else
    {
        owned = read_all_lines(stdin, &line_count);
        if (owned == NULL || line_count == 0U)
        {
            free_string_array(owned, line_count);
            return EXIT_SUCCESS;
        }

        for (i = 0U; i < line_count; i++)
        {
            if (!tokenize_string(owned[i], &words, &count, &capacity))
            {
                free_string_array(words, count);
                free_string_array(owned, line_count);
                return EXIT_FAILURE;
            }
        }

        free_string_array(owned, line_count);
        owned = NULL;
    }

    if (count >= 2U && (is_count_token(words[0], count - 1U) || is_count_token(words[0], count - 2U)))
    {
        free(words[0]);
        memmove(words, words + 1, (count - 1U) * sizeof(*words));
        count--;
    }

    if (count > 0U)
    {
        length = strlen(words[count - 1U]);
        if (length > 0U && words[count - 1U][length - 1U] == ' ')
        {
            words[count - 1U][length - 1U] = '\0';
        }
    }

    if (count < 2U)
    {
        free_string_array(words, count);
        return EXIT_SUCCESS;
    }

    result = concat_adjacent_elements((const char *const *)words, count, &result_count);
    if (result == NULL)
    {
        fprintf(stderr, "Error: failed to concatenate adjacent elements.\n");
        free_string_array(words, count);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < result_count; i++)
    {
        printf("%s\n", result[i]);
    }

    free_string_array(result, result_count);
    free_string_array(words, count);

    return EXIT_SUCCESS;
}