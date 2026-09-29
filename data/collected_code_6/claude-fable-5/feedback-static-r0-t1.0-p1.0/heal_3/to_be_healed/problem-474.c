#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

size_t replace_chars(char *str, size_t max_len, char old_char, char new_char);

size_t replace_chars(char *str, size_t max_len, char old_char, char new_char)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    if (old_char == '\0' || new_char == '\0') {
        return 0;
    }

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        if (str[i] == old_char) {
            str[i] = new_char;
            count++;
        }
    }

    return count;
}

int main(void)
{
    const char source[] = "hello world, hello everyone";
    size_t len;
    size_t buffer_size;
    char *buffer;
    size_t replaced;

    len = strnlen(source, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input string too long or not terminated\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  buffer_size is assigned 'len+1' here.
     */
    buffer_size = len + 1;
    buffer = malloc(buffer_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Condition 'len>=buffer_size' is always false
     *  Condition 'len>=buffer_size' is always false [knownConditionTrueFalse]
     */
    if (len >= buffer_size) {
        fprintf(stderr, "Buffer too small for copy\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, source, len);
    buffer[len] = '\0';

    printf("Original: %s\n", buffer);

    replaced = replace_chars(buffer, buffer_size, 'l', 'L');

    printf("Modified: %s\n", buffer);
    printf("Replacements made: %zu\n", replaced);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}