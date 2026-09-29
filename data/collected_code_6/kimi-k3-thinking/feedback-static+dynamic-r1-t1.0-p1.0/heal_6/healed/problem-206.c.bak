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

    for (i = 0U; i + 1U < count; i++)
    {
        size_t left_len = strlen(elements[i]);
        size_t right_len = strlen(elements[i + 1U]);
        size_t trailing = (i + 2U < count) ? 1U : 0U;
        size_t size;

        if (right_len > SIZE_MAX - left_len - 2U)
        {
            free_string_array(result, i);
            return NULL;
        }

        size = left_len + 1U + right_len + trailing + 1U;
        result[i] = malloc(size);
        if (result[i] == NULL)
        {
            free_string_array(result, i);
            return NULL;
        }

        memcpy(result[i], elements[i], left_len);
        result[i][left_len] = ' ';
        memcpy(result[i] + left_len + 1U, elements[i + 1U], right_len);
        if (trailing)
        {
            result[i][left_len + 1U + right_len] = ' ';
        }
        result[i][size - 1U] = '\0';
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

static int is_delimiter(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f';
}

static int append_word(char ***words, size_t *count, size_t *capacity, const char *start, size_t length)
{
    char *word;

    if (words == NULL || count == NULL || capacity == NULL || start == NULL || length == 0U)
    {
        return 0;
    }

    if (*count == *capacity)
    {
        size_t new_capacity = (*capacity == 0U) ? 8U : (*capacity * 2U);
        char **new_words;

        if (new_capacity <= *capacity || new_capacity > SIZE_MAX / sizeof(*new_words))
        {
            return 0;
        }

        new_words = realloc(*words, new_capacity * sizeof(*new_words));
        if (new_words == NULL)
        {
            return 0;
        }

        *words = new_words;
        *capacity = new_capacity;
    }

    if (length == SIZE_MAX)
    {
        return 0;
    }

    word = malloc(length + 1U);
    if (word == NULL)
    {
        return 0;
    }

    memcpy(word, start, length);
    word[length] = '\0';

    (*words)[*count] = word;
    *count += 1U;
    return 1;
}

static int tokenize_string(const char *text, char ***words, size_t *count, size_t *capacity)
{
    size_t i = 0U;

    if (text == NULL)
    {
        return 1;
    }

    while (text[i] != '\0')
    {
        size_t start;

        while (text[i] != '\0' && is_delimiter(text[i]))
        {
            i++;
        }
        if (text[i] == '\0')
        {
            break;
        }

        start = i;
        while (text[i] != '\0' && !is_delimiter(text[i]))
        {
            i++;
        }

        if (!append_word(words, count, capacity, text + start, i - start))
        {
            return 0;
        }
    }

    return 1;
}

static int parse_number(const char *text, size_t *out_value)
{
    size_t value = 0U;
    size_t length;
    size_t i;

    if (text == NULL || out_value == NULL)
    {
        return 0;
    }

    length = strlen(text);
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

    *out_value = value;
    return 1;
}

int main(int argc, const char *argv[])
{
    char **lines = NULL;
    char **words = NULL;
    char **result = NULL;
    size_t line_count = 0U;
    size_t count = 0U;
    size_t capacity = 0U;
    size_t result_count = 0U;
    size_t number = 0U;
    size_t i;

    if (argc >= 2)
    {
        for (i = 1U; i < (size_t)argc; i++)
        {
            if (!tokenize_string(argv[i], &words, &count, &capacity))
            {
                free_string_array(words, count);
                return EXIT_FAILURE;
            }
        }
    }
    else
    {
        lines = read_all_lines(stdin, &line_count);
        if (lines == NULL || line_count == 0U)
        {
            free_string_array(lines, line_count);
            return EXIT_SUCCESS;
        }

        for (i = 0U; i < line_count; i++)
        {
            if (!tokenize_string(lines[i], &words, &count, &capacity))
            {
                free_string_array(words, count);
                free_string_array(lines, line_count);
                return EXIT_FAILURE;
            }
        }

        free_string_array(lines, line_count);
        lines = NULL;
    }

    if (count >= 2U && parse_number(words[0], &number) &&
        (number == count - 1U || number == count - 2U))
    {
        free(words[0]);
        memmove(words, words + 1, (count - 1U) * sizeof(*words));
        count--;
    }

    if (count < 2U)
    {
        free_string_array(words, count);
        return EXIT_SUCCESS;
    }

    result = concat_adjacent_elements((const char *const *)words, count, &result_count);
    if (result == NULL)
    {
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