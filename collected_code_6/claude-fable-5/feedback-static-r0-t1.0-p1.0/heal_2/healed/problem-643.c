#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int contains_interior_z(const char *word, size_t len)
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

int find_word_with_interior_z(const char *text, char *result, size_t result_size)
{
    size_t i = 0;

    if (text == NULL || result == NULL || result_size == 0) {
        return -1;
    }

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
            for (size_t j = 0; j < len && j < result_size - 1; j++) {
                result[j] = text[start + j];
            }
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
    char buffer[256];

    memset(buffer, 0, sizeof(buffer));

    for (size_t i = 0; i < num_tests; i++) {
        const int status = find_word_with_interior_z(tests[i], buffer, sizeof(buffer));
        if (status == 0) {
            printf("Input: \"%s\" -> Match: \"%s\"\n", tests[i], buffer);
        } else if (status == 1) {
            printf("Input: \"%s\" -> No match found\n", tests[i]);
        } else {
            fprintf(stderr, "Error processing input: \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}