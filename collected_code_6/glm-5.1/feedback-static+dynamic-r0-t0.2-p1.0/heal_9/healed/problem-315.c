#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_first_max_even_word(const char *str, char *result, size_t result_size) {
    if (str == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    int max_len = 0;
    int found = 0;
    const char *start = NULL;

    while (*str != '\0') {
        while (*str == ' ') {
            str++;
        }

        if (*str == '\0') {
            break;
        }

        const char *word_start = str;
        while (*str != '\0' && *str != ' ') {
            str++;
        }

        int len = str - word_start;

        if (len % 2 == 0) {
            if (len > max_len) {
                max_len = len;
                start = word_start;
                found = 1;
            }
        }
    }

    if (found) {
        size_t copy_len = (size_t)max_len;
        if (copy_len >= result_size) {
            copy_len = result_size - 1;
        }
        memcpy(result, start, copy_len);
        result[copy_len] = '\0';
        return (int)copy_len;
    }

    result[0] = '\0';
    return 0;
}

int main() {
    const size_t max_result_len = 256;
    char *input = strdup("This is a test string with some even and odd words");
    char *result = malloc(max_result_len);

    if (input == NULL || result == NULL) {
        free(input);
        free(result);
        return 1;
    }

    int len = find_first_max_even_word(input, result, max_result_len);

    if (len > 0) {
        printf("%s\n", result);
    } else {
        printf("No even length word found\n");
    }

    free(input);
    free(result);
    return 0;
}