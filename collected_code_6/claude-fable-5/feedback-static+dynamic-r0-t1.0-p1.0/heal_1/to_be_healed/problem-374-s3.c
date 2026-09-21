#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (input == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len == 0) {
        return -1;
    }

    buffer = malloc(len + 1);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, input, len + 1);
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