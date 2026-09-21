#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_TEXT_LEN 256

int match_word_with_z(const char *text, char *result, size_t result_size)
{
    size_t i = 0;

    if (text == NULL || result == NULL || result_size == 0) {
        return 0;
    }

    result[0] = '\0';

    while (text[i] != '\0') {
        while (text[i] != '\0' && !isalpha((unsigned char)text[i])) {
            i++;
        }
        if (text[i] == '\0') {
            break;
        }

        {
            size_t start = i;
            int has_z = 0;

            while (text[i] != '\0' && isalpha((unsigned char)text[i])) {
                if (tolower((unsigned char)text[i]) == 'z') {
                    has_z = 1;
                }
                i++;
            }

            if (has_z) {
                size_t len = i - start;
                size_t j;

                if (len >= result_size) {
                    return 0;
                }

                for (j = 0; j < len && j < result_size - 1; j++) {
                    result[j] = text[start + j];
                }
                result[j] = '\0';
                return 1;
            }
        }
    }
    return 0;
}

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t n = 0;

    while (n < max_len && s[n] != '\0') {
        n++;
    }
    return n;
}

int main(void)
{
    static const char text[] = "The lazy dog jumped over the fence";
    size_t text_len;
    size_t buffer_size;
    char *result;

    text_len = bounded_strlen(text, MAX_TEXT_LEN);
    if (text_len == 0 || text_len >= MAX_TEXT_LEN) {
        return EXIT_FAILURE;
    }

    buffer_size = text_len + 1;

    result = (char *)malloc(buffer_size);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    memset(result, 0, buffer_size);

    if (match_word_with_z(text, result, buffer_size)) {
        if (printf("Found word: %s\n", result) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No word containing 'z' found\n") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}