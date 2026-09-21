#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

static int contains_interior_z(const char *word, size_t len)
{
    if (word == NULL || len < 3) {
        return 0;
    }

    for (size_t i = 1; i < len - 1; i++) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return 1;
        }
    }

    return 0;
}

static int find_word_with_interior_z(const char *text, char *result, size_t result_size)
{
    size_t i = 0;

    if (text == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    result[0] = '\0';

    while (text[i] != '\0') {
        while (text[i] != '\0' && !isalpha((unsigned char)text[i])) {
            i++;
        }

        const size_t start = i;

        while (text[i] != '\0' && isalpha((unsigned char)text[i])) {
            i++;
        }

        const size_t len = i - start;

        if (len > 0 && contains_interior_z(text + start, len)) {
            if (len >= result_size) {
                return -1;
            }
            memcpy(result, text + start, len);
            result[len] = '\0';
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    const char *tests[] = {
        "the lazy dog jumped",
        "zebra runs fast",
        "jazz music is nice",
        "no matching words here",
        "amazing puzzle pieces"
    };
    const size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    size_t max_len = 0;
    for (size_t i = 0; i < num_tests; i++) {
        const size_t len = strnlen(tests[i], MAX_INPUT_LEN);
        if (len >= MAX_INPUT_LEN) {
            fprintf(stderr, "Input string too long or not terminated\n");
            return EXIT_FAILURE;
        }
        if (len > max_len) {
            max_len = len;
        }
    }

    const size_t buffer_size = max_len + 1;
    char *buffer = calloc(buffer_size, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_tests; i++) {
        const int status = find_word_with_interior_z(tests[i], buffer, buffer_size);
        if (status == 0) {
            printf("Input: \"%s\" -> Match: \"%s\"\n", tests[i], buffer);
        } else if (status == 1) {
            printf("Input: \"%s\" -> No match found\n", tests[i]);
        } else {
            fprintf(stderr, "Error processing input: \"%s\"\n", tests[i]);
            free(buffer);
            return EXIT_FAILURE;
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}