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

static int permute(char *str, size_t left, size_t right)
{
    size_t i;

    if (left == right) {
        if (puts(str) == EOF) {
            return -1;
        }
        return 0;
    }

    for (i = left; i <= right; i++) {
        swap_chars(&str[left], &str[i]);
        if (permute(str, left + 1, right) != 0) {
            swap_chars(&str[left], &str[i]);
            return -1;
        }
        swap_chars(&str[left], &str[i]);
    }

    return 0;
}

static int print_permutations(const char *input)
{
    size_t len;
    size_t alloc_size;
    char *copy;
    int result;

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

    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    alloc_size = len + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<len' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size<len' is always false
     */
    if (alloc_size < len) {
        return -1;
    }

    copy = malloc(alloc_size);
    if (copy == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, input, len);
    copy[len] = '\0';

    result = permute(copy, 0, len - 1);

    free(copy);
    return result;
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