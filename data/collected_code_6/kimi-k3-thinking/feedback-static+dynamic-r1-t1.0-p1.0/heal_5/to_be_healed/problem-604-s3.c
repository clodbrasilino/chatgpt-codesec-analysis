#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void reverse_range(char *str, size_t start, size_t end)
{
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

static char *read_line(FILE *stream, size_t *out_len)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);
    if (buffer == NULL)
    {
        return NULL;
    }

    int ch;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n')
    {
        if (length + 1 >= capacity)
        {
            if (capacity > SIZE_MAX / 2)
            {
                free(buffer);
                return NULL;
            }
            size_t new_capacity = capacity * 2;
            if (new_capacity <= capacity)
            {
                free(buffer);
                return NULL;
            }
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        if (length >= capacity - 1)
        {
            free(buffer);
            return NULL;
        }
        buffer[length] = (char)ch;
        length++;
    }

    if (ferror(stream) != 0 || (ch == EOF && length == 0))
    {
        free(buffer);
        return NULL;
    }

    const char *cr = memchr(buffer, '\r', length);
    if (cr != NULL)
    {
        length = (size_t)(cr - buffer);
    }

    buffer[length] = '\0';

    if (out_len != NULL)
    {
        *out_len = length;
    }

    return buffer;
}

char *reverse_words(const char *str, size_t len)
{
    if (str == NULL)
    {
        return NULL;
    }

    if (len == SIZE_MAX)
    {
        return NULL;
    }

    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    size_t alloc_size = len + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<=len' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size<=len' is always false
     */
    if (alloc_size <= len)
    {
        return NULL;
    }

    char *result = malloc(alloc_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (result == NULL)
    {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'len>=alloc_size' is always false [knownConditionTrueFalse]
     *  Condition 'len>=alloc_size' is always false
     */
    if (len >= alloc_size)
    {
        free(result);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, str, len);
    result[len] = '\0';

    if (len > 0)
    {
        reverse_range(result, 0, len - 1);
    }

    size_t word_start = 0;
    for (size_t i = 0; i <= len; i++)
    {
        if (result[i] == ' ' || result[i] == '\0')
        {
            if (word_start < i)
            {
                reverse_range(result, word_start, i - 1);
            }
            word_start = i + 1;
        }
    }

    return result;
}

int main(void)
{
    char *input;
    size_t len = 0;

    while ((input = read_line(stdin, &len)) != NULL)
    {
        char *reversed = reverse_words(input, len);
        free(input);

        if (reversed == NULL)
        {
            fprintf(stderr, "Error: failed to reverse words\n");
            return EXIT_FAILURE;
        }

        fputs(reversed, stdout);
        putchar('\n');

        free(reversed);
    }

    if (ferror(stdin) != 0)
    {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}