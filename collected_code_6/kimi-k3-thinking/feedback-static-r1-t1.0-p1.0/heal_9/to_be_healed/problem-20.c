#include <stdio.h>
#include <stdlib.h>
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
    int c;

    buffer = malloc(capacity);

    if (buffer == NULL)
    {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stream)) != EOF)
    {
        if (c == '\n')
        {
            break;
        }

        if (length + 2 > capacity)
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

            if (new_capacity < length + 2)
            {
                new_capacity = length + 2;
            }

            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL)
            {
                free(buffer);
                errno = ENOMEM;
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length] = (char)c;
        length++;
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