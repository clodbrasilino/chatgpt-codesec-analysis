#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

bool find_max_occurring_char(const char *str, char *result)
{
    int freq[256] = {0};
    int max_count = 0;
    size_t i;

    if (str == NULL || result == NULL || str[0] == '\0')
    {
        return false;
    }

    for (i = 0; str[i] != '\0'; i++)
    {
        freq[(unsigned char)str[i]]++;
    }

    for (i = 0; i < 256; i++)
    {
        if (freq[i] > max_count)
        {
            max_count = freq[i];
            *result = (char)i;
        }
    }

    return true;
}

char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int c;

    if (stream == NULL)
    {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL)
    {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stream)) != EOF && c != '\n')
    {
        if (length + 1 >= capacity)
        {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2)
            {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;

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

        buffer[length++] = (char)c;
    }

    if (ferror(stream))
    {
        free(buffer);
        return NULL;
    }

    if (c == EOF && length == 0)
    {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    char result = '\0';

    printf("Enter a string: ");
    fflush(stdout);

    input = read_line(stdin);

    if (input == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    if (!find_max_occurring_char(input, &result))
    {
        fprintf(stderr, "Invalid or empty input string.\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("The maximum occurring character is '%c'.\n", result);

    free(input);
    return EXIT_SUCCESS;
}