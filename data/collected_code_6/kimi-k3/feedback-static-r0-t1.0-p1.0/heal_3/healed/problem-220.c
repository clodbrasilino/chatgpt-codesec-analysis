#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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
    size_t n = 0;
    char *endptr;
    char input_buffer[256];

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
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        free(str);
        return 1;
    }

    if (strchr(input_buffer, '\n') == NULL && !feof(stdin))
    {
        fprintf(stderr, "Input too long\n");
        free(str);
        return 1;
    }

    errno = 0;
    n = strtoull(input_buffer, &endptr, 10);
    
    if (errno != 0 || endptr == input_buffer || (*endptr != '\n' && *endptr != '\0'))
    {
        fprintf(stderr, "Invalid input\n");
        free(str);
        return 1;
    }

    replace_max_n(str, n);

    printf("Result: %s\n", str);

    free(str);
    return 0;
}