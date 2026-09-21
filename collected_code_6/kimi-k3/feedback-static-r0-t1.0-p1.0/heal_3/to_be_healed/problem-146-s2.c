#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#define INITIAL_BUFFER_SIZE 256

int sum_ascii_values(const char *str, size_t str_len, int *result)
{
    int sum;
    size_t i;

    if (str == NULL || result == NULL)
    {
        return -1;
    }

    sum = 0;

    for (i = 0; i < str_len; i++)
    {
        if (sum > INT_MAX - (unsigned char)str[i])
        {
            return -2;
        }
        sum += (unsigned char)str[i];
    }

    *result = sum;
    return 0;
}

int read_line(char **buffer, size_t *length)
{
    size_t capacity;
    size_t len;
    char *buf;
    int c;

    if (buffer == NULL || length == NULL)
    {
        return -1;
    }

    capacity = INITIAL_BUFFER_SIZE;
    len = 0;

    buf = malloc(capacity);
    if (buf == NULL)
    {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n')
    {
        if (len + 1 >= capacity)
        {
            size_t new_capacity = capacity * 2;
            char *new_buf;

            if (new_capacity < capacity)
            {
                free(buf);
                return -1;
            }

            new_buf = realloc(buf, new_capacity);
            if (new_buf == NULL)
            {
                free(buf);
                return -1;
            }

            buf = new_buf;
            capacity = new_capacity;
        }

        buf[len++] = (char)c;
    }

    if (c == EOF && len == 0)
    {
        free(buf);
        return -1;
    }

    buf[len] = '\0';

    *buffer = buf;
    *length = len;
    return 0;
}

int main(void)
{
    char *buffer;
    size_t len;
    int total;
    int status;

    buffer = NULL;
    len = 0;

    printf("Enter a string: ");

    if (read_line(&buffer, &len) != 0)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    status = sum_ascii_values(buffer, len, &total);

    if (status == 0)
    {
        printf("Total ASCII value: %d\n", total);
    }
    else if (status == -2)
    {
        fprintf(stderr, "Error: Integer overflow occurred\n");
        free(buffer);
        return 1;
    }
    else
    {
        fprintf(stderr, "Error: Invalid input\n");
        free(buffer);
        return 1;
    }

    free(buffer);
    return 0;
}