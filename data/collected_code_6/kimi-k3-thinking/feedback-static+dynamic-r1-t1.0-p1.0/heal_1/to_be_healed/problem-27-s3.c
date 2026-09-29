#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str)
{
    char *read_ptr;
    char *write_ptr;

    if (str == NULL)
    {
        return;
    }

    read_ptr = str;
    write_ptr = str;

    while (*read_ptr != '\0')
    {
        if (!isdigit((unsigned char)*read_ptr))
        {
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
    *write_ptr = '\0';
}

int main(void)
{
    const size_t num_strings = 4;
    const char *input_strings[] = {
        "abc123def",
        "h3ll0 w0rld",
        "no digits here",
        "9876543210"
    };
    char **strings = NULL;
    size_t i;
    size_t j;

    strings = malloc(num_strings * sizeof(char *));
    if (strings == NULL)
    {
        fprintf(stderr, "Error: failed to allocate string array\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < num_strings; i++)
    {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        strings[i] = malloc(strlen(input_strings[i]) + 1);
        if (strings[i] == NULL)
        {
            fprintf(stderr, "Error: failed to allocate string %zu\n", i);
            for (j = 0; j < i; j++)
            {
                free(strings[j]);
                strings[j] = NULL;
            }
            free(strings);
            strings = NULL;
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(strings[i], input_strings[i]);
    }

    for (i = 0; i < num_strings; i++)
    {
        remove_digits(strings[i]);
        if (printf("Result %zu: \"%s\"\n", i, strings[i]) < 0)
        {
            fprintf(stderr, "Error: failed to write output\n");
            for (j = 0; j < num_strings; j++)
            {
                free(strings[j]);
                strings[j] = NULL;
            }
            free(strings);
            strings = NULL;
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < num_strings; i++)
    {
        free(strings[i]);
        strings[i] = NULL;
    }
    free(strings);
    strings = NULL;

    return EXIT_SUCCESS;
}