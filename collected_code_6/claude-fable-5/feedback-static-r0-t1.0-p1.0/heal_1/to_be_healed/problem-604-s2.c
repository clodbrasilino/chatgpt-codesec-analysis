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
    /* Possible weaknesses found:
     *  The scope of the variable 'word_start' can be reduced. [variableScope]
     */
    size_t word_start;

    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
        word_start = i;
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t buf_size = strlen(input) + 1;
    char *buffer = malloc(buf_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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