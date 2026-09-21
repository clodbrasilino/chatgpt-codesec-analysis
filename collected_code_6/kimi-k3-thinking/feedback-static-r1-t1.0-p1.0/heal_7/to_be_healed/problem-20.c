#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

int is_woodall(long long num)
{
    long long n;
    long long power;

    if (num < 1)
    {
        return 0;
    }

    n = 1;
    power = 2;

    while (1)
    {
        long long woodall;

        if (power > LLONG_MAX / n)
        {
            break;
        }

        woodall = n * power - 1;

        if (woodall == num)
        {
            return 1;
        }

        if (woodall > num)
        {
            break;
        }

        if (power > LLONG_MAX / 2)
        {
            break;
        }

        power = power * 2;
        n = n + 1;
    }

    return 0;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char chunk[64];
    int done = 0;

    buffer = malloc(capacity);

    if (buffer == NULL)
    {
        return NULL;
    }

    buffer[0] = '\0';

    while (!done)
    {
        size_t chunk_length;

        if (fgets(chunk, sizeof(chunk), stream) == NULL)
        {
            if (ferror(stream) || length == 0)
            {
                free(buffer);
                return NULL;
            }

            break;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        chunk_length = strlen(chunk);

        if (chunk_length > 0 && chunk[chunk_length - 1] == '\n')
        {
            chunk[chunk_length - 1] = '\0';
            chunk_length--;
            done = 1;
        }

        while (capacity - length < chunk_length + 1)
        {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2)
            {
                free(buffer);
                errno = ENOMEM;
                return NULL;
            }

            new_capacity = capacity * 2;

            if (new_capacity <= capacity)
            {
                free(buffer);
                errno = ENOMEM;
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

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer + length, chunk, chunk_length + 1);
        length += chunk_length;
    }

    return buffer;
}

int main(void)
{
    char *buffer;
    char *endptr;
    long long num;

    printf("Enter a number: ");
    fflush(stdout);

    buffer = read_line(stdin);

    if (buffer == NULL)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    errno = 0;
    num = strtoll(buffer, &endptr, 10);

    if (errno == ERANGE || endptr == buffer || *endptr != '\0')
    {
        fprintf(stderr, "Error: invalid input.\n");
        free(buffer);
        return 1;
    }

    free(buffer);

    if (is_woodall(num))
    {
        printf("%lld is a Woodall number.\n", num);
    }
    else
    {
        printf("%lld is not a Woodall number.\n", num);
    }

    return 0;
}