#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int match_word_with_z(const char *text, char *result, size_t result_size)
{
    size_t i = 0;
    size_t start;
    size_t len;
    int has_z;

    if (text == NULL || result == NULL || result_size == 0) {
        return 0;
    }

    while (text[i] != '\0') {
        while (text[i] != '\0' && !isalpha((unsigned char)text[i])) {
            i++;
        }
        if (text[i] == '\0') {
            break;
        }
        start = i;
        has_z = 0;
        while (text[i] != '\0' && isalpha((unsigned char)text[i])) {
            if (tolower((unsigned char)text[i]) == 'z') {
                has_z = 1;
            }
            i++;
        }
        if (has_z) {
            len = i - start;
            if (len >= result_size) {
                return 0;
            }
            memcpy(result, &text[start], len);
            result[len] = '\0';
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    const char *text = "The lazy dog jumped over the fence";
    char result[256];

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