#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

size_t shortest_word_length(const char *str)
{
    size_t min_len;
    size_t current_len;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    min_len = SIZE_MAX;
    current_len = 0;

    for (i = 0; ; i++) {
        if (str[i] != '\0' && !isspace((unsigned char)str[i])) {
            current_len++;
        } else {
            if (current_len > 0 && current_len < min_len) {
                min_len = current_len;
            }
            current_len = 0;
        }
        if (str[i] == '\0') {
            break;
        }
    }

    if (min_len == SIZE_MAX) {
        return 0;
    }

    return min_len;
}

int main(void)
{
    const char *test1 = "The quick brown fox jumps over a lazy dog";
    const char *test2 = "hello world";
    const char *test3 = "";
    const char *test4 = "   ";
    size_t result;

    result = shortest_word_length(test1);
    if (printf("Shortest word length in \"%s\": %zu\n", test1, result) < 0) {
        return EXIT_FAILURE;
    }

    result = shortest_word_length(test2);
    if (printf("Shortest word length in \"%s\": %zu\n", test2, result) < 0) {
        return EXIT_FAILURE;
    }

    result = shortest_word_length(test3);
    if (printf("Shortest word length in \"%s\": %zu\n", test3, result) < 0) {
        return EXIT_FAILURE;
    }

    result = shortest_word_length(test4);
    if (printf("Shortest word length in \"%s\": %zu\n", test4, result) < 0) {
        return EXIT_FAILURE;
    }

    result = shortest_word_length(NULL);
    if (printf("Shortest word length in NULL: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}