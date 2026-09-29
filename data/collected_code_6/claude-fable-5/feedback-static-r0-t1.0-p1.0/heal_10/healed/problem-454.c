#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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
                    result[0] = '\0';
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

int main(void)
{
    const char *text = "The lazy dog jumped over the fence";
    char result[256];

    memset(result, 0, sizeof(result));

    if (match_word_with_z(text, result, sizeof(result))) {
        if (printf("Found word: %s\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No word containing 'z' found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}