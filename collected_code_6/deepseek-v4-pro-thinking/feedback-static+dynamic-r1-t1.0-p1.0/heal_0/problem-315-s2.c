#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

const char *find_first_max_even_word(const char *str, size_t *length)
{
    const char *result = NULL;
    size_t max_len = 0;
    const char *start;
    size_t len;

    if (str == NULL) {
        if (length != NULL)
            *length = 0;
        return NULL;
    }
    if (length == NULL)
        return NULL;

    *length = 0;

    while (*str != '\0') {
        while (*str != '\0' && isspace((unsigned char)*str))
            str++;

        if (*str == '\0')
            break;

        start = str;
        len = 0;

        while (*str != '\0' && !isspace((unsigned char)*str)) {
            str++;
            len++;
        }

        if (len % 2 == 0 && len > max_len) {
            max_len = len;
            result = start;
        }
    }

    *length = max_len;
    return result;
}

int main(void)
{
    char text[] = "The quick brown fox jumps over lazy dog";
    size_t length = 0;
    const char *word = find_first_max_even_word(text, &length);

    if (word != NULL) {
        printf("First max even word: ");
        printf("%.*s\n", (int)length, word);
        printf("Length: %zu\n", length);
    } else {
        printf("No even word found.\n");
    }

    return 0;
}