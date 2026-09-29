#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 1024U

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
        if (permute(str, left + 1U, right) != 0) {
            swap_chars(&str[left], &str[i]);
            return -1;
        }
        swap_chars(&str[left], &str[i]);
    }

    return 0;
}

static int print_permutations(const char *input)
{
    char *buffer;
    size_t len;
    size_t buf_size;
    int result;

    if (input == NULL) {
        return -1;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len == 0U || len >= MAX_INPUT_LEN) {
        return -1;
    }

    /* Possible weaknesses found:
     *  buf_size is assigned 'len+1U' here.
     */
    buf_size = len + 1U;

    /* Possible weaknesses found:
     *  Condition 'buf_size<=len' is always false
     *  Condition 'buf_size<=len' is always false [knownConditionTrueFalse]
     */
    if (buf_size <= len) {
        return -1;
    }

    buffer = malloc(buf_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  Condition 'len>=buf_size' is always false [knownConditionTrueFalse]
     *  Condition 'len>=buf_size' is always false
     */
    if (len >= buf_size) {
        free(buffer);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, input, len);
    buffer[len] = '\0';

    result = permute(buffer, 0U, len - 1U);

    free(buffer);

    return result;
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