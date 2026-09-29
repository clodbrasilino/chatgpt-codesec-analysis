#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (input == NULL) {
        return -1;
    }

    len = strnlen(input, MAX_INPUT_LEN + 1U);
    if (len == 0U || len > MAX_INPUT_LEN) {
        return -1;
    }

    buffer = (char *)malloc(len + 1U);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, input, len);
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