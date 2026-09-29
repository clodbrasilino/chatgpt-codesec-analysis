#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define BUFFER_SIZE 1024

char *find_first_max_even_word(const char *str, size_t *out_len)
{
    size_t i = 0;
    size_t best_start = 0;
    size_t best_len = 0;
    size_t dest_size = 0;
    size_t j = 0;
    char *result = NULL;

    if (str == NULL)
    {
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

    if (best_len == 0 || best_len == SIZE_MAX)
    {
        return NULL;
    }

    dest_size = best_len + 1;

    result = (char *)malloc(dest_size);
    if (result == NULL)
    {
        return NULL;
    }

    for (j = 0; j < best_len; j++)
    {
        result[j] = str[best_start + j];
    }
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
    char *word = NULL;
    size_t word_len = 0;

    buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        free(buffer);
        buffer = NULL;
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    word = find_first_max_even_word(buffer, &word_len);

    free(buffer);
    buffer = NULL;

    if (word == NULL)
    {
        printf("No even-length word found.\n");
        return EXIT_SUCCESS;
    }

    printf("First maximum length even word: %s\n", word);
    printf("Length: %zu\n", word_len);

    free(word);
    word = NULL;

    return EXIT_SUCCESS;
}