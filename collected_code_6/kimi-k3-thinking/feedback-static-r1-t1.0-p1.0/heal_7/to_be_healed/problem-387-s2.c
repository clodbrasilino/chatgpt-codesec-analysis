#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#define READ_LINE_CHUNK_SIZE 128

static char *read_line(FILE *stream, size_t *out_length)
{
    size_t capacity = READ_LINE_CHUNK_SIZE;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL)
    {
        return NULL;
    }

    for (;;)
    {
        if (capacity - length < 2)
        {
            size_t new_capacity = (capacity > SIZE_MAX / 2) ? SIZE_MAX : capacity * 2;

            if (new_capacity <= capacity)
            {
                free(buffer);
                return NULL;
            }

            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL)
            {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        size_t space = capacity - length;
        int request = (space > (size_t)INT_MAX) ? INT_MAX : (int)space;

        if (fgets(buffer + length, request, stream) == NULL)
        {
            if (ferror(stream))
            {
                free(buffer);
                return NULL;
            }
            break;
        }

        char *segment = buffer + length;
        /* Possible weaknesses found:
         *  Variable 'terminator' can be declared as pointer to const [constVariablePointer]
         */
        char *terminator = memchr(segment, '\0', (size_t)request);
        size_t segment_length = (terminator != NULL)
                                ? (size_t)(terminator - segment)
                                : (size_t)request - 1;
        int line_complete = 0;

        if (segment_length > 0 && segment[segment_length - 1] == '\n')
        {
            line_complete = 1;
            length += segment_length - 1;
        }
        else
        {
            length += segment_length;
        }

        if (line_complete || segment_length < (size_t)request - 1)
        {
            break;
        }
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