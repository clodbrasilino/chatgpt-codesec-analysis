#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

static char *read_line(FILE *stream, size_t *out_length)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL)
    {
        return NULL;
    }

    for (;;)
    {
        int c = fgetc(stream);

        if (c == EOF)
        {
            if (ferror(stream))
            {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (c == '\n')
        {
            break;
        }

        if (length + 1 >= capacity)
        {
            if (capacity > SIZE_MAX / 2)
            {
                free(buffer);
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL)
            {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)c;
    }

    buffer[length] = '\0';

    if (out_length != NULL)
    {
        *out_length = length;
    }

    return buffer;
}

int main(void)
{
    size_t length = 0;
    char *buffer = read_line(stdin, &length);

    if (buffer == NULL)
    {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    printf("Input length: %zu\n", length);

    free(buffer);
    return EXIT_SUCCESS;
}