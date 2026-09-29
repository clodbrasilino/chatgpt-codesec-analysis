#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_word_boundary(char c)
{
    return c == '\0' || isspace((unsigned char)c) || ispunct((unsigned char)c);
}

char *abbreviate_road(const char *input)
{
    const char *word = "road";
    const char *replacement = "rd.";
    size_t word_len = 4;
    size_t replacement_len = 3;
    size_t input_len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL)
    {
        return NULL;
    }

    input_len = strlen(input);

    result = malloc(input_len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    i = 0;
    j = 0;
    while (i < input_len)
    {
        if ((i == 0 || is_word_boundary(input[i - 1])) &&
            i + word_len <= input_len &&
            strncmp(input + i, word, word_len) == 0 &&
            is_word_boundary(input[i + word_len]))
        {
            memcpy(result + j, replacement, replacement_len);
            j += replacement_len;
            i += word_len;
            if (i < input_len && input[i] == '.')
            {
                i++;
            }
        }
        else
        {
            result[j] = input[i];
            j++;
            i++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "Take the road down the road.",
        "The road is long and winding.",
        "No abbreviation needed here.",
        "road trip ahead on this road"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t k;

    for (k = 0; k < num_tests; k++)
    {
        char *abbreviated = abbreviate_road(test_strings[k]);
        if (abbreviated == NULL)
        {
            fprintf(stderr, "Error: failed to process string %zu\n", k);
            return EXIT_FAILURE;
        }

        printf("Original:    %s\n", test_strings[k]);
        printf("Abbreviated: %s\n\n", abbreviated);

        free(abbreviated);
        abbreviated = NULL;
    }

    return EXIT_SUCCESS;
}