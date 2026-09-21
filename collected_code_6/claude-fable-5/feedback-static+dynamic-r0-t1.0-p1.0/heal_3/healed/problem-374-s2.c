#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 64U

static void swap_chars(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

static void permute(char *str, size_t left, size_t right)
{
    size_t i;

    if (left == right) {
        if (puts(str) == EOF) {
            exit(EXIT_FAILURE);
        }
        return;
    }

    for (i = left; i <= right; i++) {
        swap_chars(&str[left], &str[i]);
        permute(str, left + 1U, right);
        swap_chars(&str[left], &str[i]);
    }
}

static int print_permutations(const char *input)
{
    char *buffer;
    size_t len;
    size_t buffer_size;
    size_t i;

    if (input == NULL) {
        return -1;
    }

    len = strnlen(input, MAX_INPUT_LEN + 1U);
    if (len == 0U || len > MAX_INPUT_LEN) {
        return -1;
    }

    if (len > SIZE_MAX - 1U) {
        return -1;
    }

    buffer_size = len + 1U;
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return -1;
    }

    for (i = 0U; i < len; i++) {
        buffer[i] = input[i];
    }
    buffer[len] = '\0';

    permute(buffer, 0U, len - 1U);
    free(buffer);

    return 0;
}

int main(void)
{
    const char *test = "ABC";

    if (print_permutations(test) != 0) {
        (void)fprintf(stderr, "Failed to print permutations\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}