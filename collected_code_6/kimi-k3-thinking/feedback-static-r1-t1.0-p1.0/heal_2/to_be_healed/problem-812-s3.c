#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 65536

char *abbreviate_road(const char *input);

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0')
    {
        len++;
    }
    return len;
}

static int is_word_char(int c)
{
    return isalnum((unsigned char)c) || c == '_';
}

static size_t road_match_len(const char *p, const char *start, const char *end)
{
    static const char word[] = "road";
    const size_t word_len = sizeof(word) - 1;

    if ((size_t)(end - p) < word_len)
    {
        return 0;
    }
    if (strncmp(p, word, word_len) != 0)
    {
        return 0;
    }
    if (p != start && is_word_char(p[-1]))
    {
        return 0;
    }
    if (p + word_len < end && is_word_char(p[word_len]))
    {
        return 0;
    }
    if (p + word_len < end && p[word_len] == '.')
    {
        return word_len + 1;
    }
    return word_len;
}

char *abbreviate_road(const char *input)
{
    static const char replacement[] = "rd.";
    const size_t repl_len = sizeof(replacement) - 1;
    size_t input_len;
    size_t saved = 0;
    size_t new_len;
    const char *p;
    const char *end;
    char *result;
    char *dest;
    size_t remaining;

    if (input == NULL)
    {
        return NULL;
    }

    input_len = bounded_strlen(input, MAX_INPUT_LEN);
    if (input_len == MAX_INPUT_LEN)
    {
        return NULL;
    }
    end = input + input_len;

    p = input;
    while (p < end && *p != '\0')
    {
        size_t m = road_match_len(p, input, end);
        if (m > 0)
        {
            saved += m - repl_len;
            p += m;
        }
        else
        {
            p++;
        }
    }

    new_len = input_len - saved + 1;

    result = malloc(new_len);
    if (result == NULL)
    {
        return NULL;
    }

    dest = result;
    remaining = new_len;
    p = input;
    while (p < end && *p != '\0')
    {
        size_t m = road_match_len(p, input, end);
        if (m > 0)
        {
            if (remaining <= repl_len)
            {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dest, replacement, repl_len);
            dest += repl_len;
            remaining -= repl_len;
            p += m;
        }
        else
        {
            if (remaining <= 1)
            {
                free(result);
                return NULL;
            }
            *dest = *p;
            dest++;
            remaining--;
            p++;
        }
    }
    *dest = '\0';

    return result;
}

int main(void)
{
    const char *text = "Take the road north, then follow the broad road.";
    char *abbreviated = abbreviate_road(text);

    if (abbreviated == NULL)
    {
        fprintf(stderr, "Error: failed to abbreviate the string.\n");
        return EXIT_FAILURE;
    }

    printf("Original:    %s\n", text);
    printf("Abbreviated: %s\n", abbreviated);

    free(abbreviated);
    abbreviated = NULL;

    return EXIT_SUCCESS;
}