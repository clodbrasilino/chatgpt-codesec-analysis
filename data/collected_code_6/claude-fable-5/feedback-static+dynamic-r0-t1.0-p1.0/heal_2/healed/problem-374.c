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
        if (puts(str) == EOF) {
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
    size_t len;
    size_t i;
    char *copy;

    if (input == NULL) {
        return -1;
    }

    len = strnlen(input, MAX_INPUT_LEN + 1);
    if (len > MAX_INPUT_LEN) {
        return -1;
    }
    if (len == 0) {
        return 0;
    }

    copy = malloc(len + 1);
    if (copy == NULL) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        copy[i] = input[i];
    }
    copy[len] = '\0';

    permute(copy, 0, len - 1);
    free(copy);
    return 0;
}

int main(void)
{
    const char *test = "abc";

    if (print_permutations(test) != 0) {
        fprintf(stderr, "Failed to print permutations\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}