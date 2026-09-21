#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#define READ_LINE_CHUNK_SIZE 128

static char *read_line(FILE *stream, size_t *out_length)
{
    size_t capacity = READ_LINE_CHUNK_SIZE;
    size_t length = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char chunk[READ_LINE_CHUNK_SIZE];
    char *buffer = malloc(capacity);

    if (buffer == NULL)
    {
        return NULL;
    }

    for (;;)
    {
        if (fgets(chunk, sizeof(chunk), stream) == NULL)
        {
            if (ferror(stream))
            {
                free(buffer);
                return NULL;
            }
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t chunk_length = strlen(chunk);
        int line_complete = 0;

        if (chunk_length > 0 && chunk[chunk_length - 1] == '\n')
        {
            chunk_length--;
            line_complete = 1;
        }

        if (chunk_length > 0)
        {
            if (chunk_length > SIZE_MAX - length - 1)
            {
                free(buffer);
                return NULL;
            }

            size_t required = length + chunk_length + 1;

            if (required > capacity)
            {
                size_t new_capacity = capacity;

                while (new_capacity < required)
                {
                    if (new_capacity > SIZE_MAX / 2)
                    {
                        new_capacity = required;
                        break;
                    }
                    new_capacity *= 2;
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

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + length, chunk, chunk_length);
            length += chunk_length;
        }

        if (line_complete || chunk_length < sizeof(chunk) - 1)
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