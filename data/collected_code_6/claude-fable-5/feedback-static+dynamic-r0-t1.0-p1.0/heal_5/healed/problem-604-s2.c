#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

static void reverse_range(char *str, size_t start, size_t end)
{
    while (start < end) {
        char tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
        start++;
        end--;
    }
}

static int reverse_words(char *str, size_t max_len)
{
    size_t len;
    size_t i;

    if (str == NULL || max_len == 0) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        return -1;
    }
    if (len == 0) {
        return 0;
    }

    reverse_range(str, 0, len - 1);

    i = 0;
    while (i < len) {
        while (i < len && str[i] == ' ') {
            i++;
        }
        if (i >= len) {
            break;
        }
        size_t word_start = i;
        while (i < len && str[i] != ' ') {
            i++;
        }
        reverse_range(str, word_start, i - 1);
    }

    return 0;
}

int main(void)
{
    const char *input = "the quick brown fox jumps over the lazy dog";
    size_t input_len = strnlen(input, MAX_INPUT_LEN);
    size_t buf_size;
    char *buffer;

    if (input_len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input string too long or not terminated\n");
        return EXIT_FAILURE;
    }

    if (input_len > SIZE_MAX - 1) {
        fprintf(stderr, "Input length overflow\n");
        return EXIT_FAILURE;
    }

    buf_size = input_len + 1;

    buffer = calloc(buf_size, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (snprintf(buffer, buf_size, "%s", input) < 0) {
        fprintf(stderr, "Failed to copy input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (reverse_words(buffer, buf_size) != 0) {
        fprintf(stderr, "Failed to reverse words\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Reversed: %s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}