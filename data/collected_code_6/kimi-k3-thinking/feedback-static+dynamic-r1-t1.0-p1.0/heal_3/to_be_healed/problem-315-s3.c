#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

char *find_first_max_even_word(const char *str, size_t *out_len)
{
    size_t i = 0;
    size_t best_start = 0;
    size_t best_len = 0;
    char *result = NULL;

    if (str == NULL)
    {
        if (out_len != NULL)
        {
            *out_len = 0;
        }
        return NULL;
    }

    while (str[i] != '\0')
    {
        while (str[i] != '\0' && isspace((unsigned char)str[i]))
        {
            i++;
        }

        if (str[i] == '\0')
        {
            break;
        }

        {
            size_t start = i;
            size_t len = 0;

            while (str[i] != '\0' && !isspace((unsigned char)str[i]))
            {
                i++;
                len++;
            }

            if (len % 2 == 0 && len > best_len)
            {
                best_start = start;
                best_len = len;
            }
        }
    }

    if (best_len == 0)
    {
        if (out_len != NULL)
        {
            *out_len = 0;
        }
        return NULL;
    }

    result = (char *)malloc(best_len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, str + best_start, best_len);
    result[best_len] = '\0';

    if (out_len != NULL)
    {
        *out_len = best_len;
    }

    return result;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_capacity = 0;
    ssize_t line_length = 0;
    char *word = NULL;
    size_t word_len = 0;

    printf("Enter a string: ");
    fflush(stdout);

    line_length = getline(&buffer, &buffer_capacity, stdin);
    if (line_length < 0)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    word = find_first_max_even_word(buffer, &word_len);

    if (word == NULL)
    {
        printf("No even-length word found.\n");
        free(buffer);
        return EXIT_SUCCESS;
    }

    printf("First maximum length even word: %s\n", word);
    printf("Length: %zu\n", word_len);

    free(word);
    word = NULL;

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}