#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 64

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
        if (printf("%s\n", str) < 0) {
            exit(EXIT_FAILURE);
        }
        return;
    }

    for (i = left; i <= right; i++) {
        swap_chars(&str[left], &str[i]);
        permute(str, left + 1, right);
        swap_chars(&str[left], &str[i]);
    }
}

static int print_permutations(const char *input)
{
    char *buffer;
    size_t len;
    size_t buffer_size;

    if (input == NULL) {
        return -1;
    }

    len = strnlen(input, MAX_INPUT_LEN + 1);
    if (len == 0 || len > MAX_INPUT_LEN) {
        return -1;
    }

    buffer_size = len + 1;

    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return -1;
    }

    memcpy(buffer, input, len);
    buffer[len] = '\0';

    permute(buffer, 0, len - 1);
    free(buffer);

    return 0;
}

int main(void)
{
    const char *test_string = "ABC";

    if (print_permutations(test_string) != 0) {
        if (fprintf(stderr, "Error: failed to print permutations\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}