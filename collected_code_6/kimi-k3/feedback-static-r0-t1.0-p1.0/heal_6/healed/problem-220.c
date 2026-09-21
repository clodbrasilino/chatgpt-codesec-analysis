#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

void replace_max_n(char *str, size_t n)
{
    size_t count = 0;
    char *p;

    if (str == NULL)
    {
        return;
    }

    p = str;
    while (*p != '\0' && count < n)
    {
        if (*p == ' ' || *p == ',' || *p == '.')
        {
            *p = ':';
            count++;
        }
        p++;
    }
}

int main(void)
{
    char *str = NULL;
    size_t str_size = 0;
    ssize_t str_len;
    unsigned long long n = 0;
    char *endptr;
    char *input_buffer = NULL;
    size_t input_buffer_size = 0;
    ssize_t input_len;

    printf("Enter a string: ");
    
    str_len = getline(&str, &str_size, stdin);
    if (str_len == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(str);
        return 1;
    }

    if (str_len > 0 && str[str_len - 1] == '\n')
    {
        str[str_len - 1] = '\0';
    }

    printf("Enter maximum number of replacements: ");
    
    input_len = getline(&input_buffer, &input_buffer_size, stdin);
    if (input_len == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(str);
        free(input_buffer);
        return 1;
    }

    if (input_len > 0 && input_buffer[input_len - 1] == '\n')
    {
        input_buffer[input_len - 1] = '\0';
    }

    errno = 0;
    n = strtoull(input_buffer, &endptr, 10);
    
    if (errno != 0 || endptr == input_buffer || *endptr != '\0')
    {
        fprintf(stderr, "Invalid input\n");
        free(str);
        free(input_buffer);
        return 1;
    }

    if (n > SIZE_MAX)
    {
        fprintf(stderr, "Input too large\n");
        free(str);
        free(input_buffer);
        return 1;
    }

    replace_max_n(str, (size_t)n);

    printf("Result: %s\n", str);

    free(str);
    free(input_buffer);
    return 0;
}