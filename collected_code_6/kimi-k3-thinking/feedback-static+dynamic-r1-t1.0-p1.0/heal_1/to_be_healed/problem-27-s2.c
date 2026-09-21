#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str)
{
    if (str == NULL)
    {
        return;
    }

    size_t read_index = 0;
    size_t write_index = 0;

    while (str[read_index] != '\0')
    {
        if (isdigit((unsigned char)str[read_index]) == 0)
        {
            str[write_index] = str[read_index];
            write_index++;
        }
        read_index++;
    }
    str[write_index] = '\0';
}

int main(void)
{
    const char *input[] = {"abc123", "h3ll0 w0rld", "98765", "no digits", "y2k2024"};
    size_t count = sizeof(input) / sizeof(input[0]);
    char **strings = malloc(count * sizeof(*strings));

    if (strings == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    size_t i;
    for (i = 0; i < count; i++)
    {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        strings[i] = malloc(strlen(input[i]) + 1);
        if (strings[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            while (i > 0)
            {
                i--;
                free(strings[i]);
            }
            free(strings);
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(strings[i], input[i]);
    }

    for (i = 0; i < count; i++)
    {
        remove_digits(strings[i]);
        printf("%s\n", strings[i]);
    }

    for (i = 0; i < count; i++)
    {
        free(strings[i]);
        strings[i] = NULL;
    }
    free(strings);
    strings = NULL;

    return EXIT_SUCCESS;
}