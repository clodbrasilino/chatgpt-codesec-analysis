#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int reverse_words(char *str)
{
    size_t len;
    size_t i;

    if (str == NULL) {
        return -1;
    }

    len = strlen(str);
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
    size_t buf_size = strlen(input) + 1;
    char *buffer = malloc(buf_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, input, buf_size);

    if (reverse_words(buffer) != 0) {
        fprintf(stderr, "Failed to reverse words\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Reversed: %s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}