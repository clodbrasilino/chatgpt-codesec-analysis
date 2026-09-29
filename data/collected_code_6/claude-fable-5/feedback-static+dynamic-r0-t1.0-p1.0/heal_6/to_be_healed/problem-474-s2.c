#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t replace_char(char *str, size_t max_len, char old_char, char new_char)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
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
    static const char original[] = "hello world, hello everyone";
    size_t len;
    size_t buffer_size;
    char *buffer;
    size_t replaced;
    size_t copy_len;

    /* Possible weaknesses found:
     *  Assignment 'len=sizeof(original)-1', assigned value is 27
     */
    len = sizeof(original) - 1;
    buffer_size = len + 1;

    buffer = malloc(buffer_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (sizeof(original) > buffer_size) {
        fprintf(stderr, "Buffer too small for source data\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assignment 'copy_len=len', assigned value is 27
     */
    copy_len = len;
    /* Possible weaknesses found:
     *  Condition 'copy_len>=buffer_size' is always false [knownConditionTrueFalse]
     *  Condition 'copy_len>=buffer_size' is always false
     */
    if (copy_len >= buffer_size) {
        copy_len = buffer_size - 1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, original, copy_len);
    buffer[copy_len] = '\0';

    replaced = replace_char(buffer, buffer_size, 'l', 'L');

    if (printf("Original: %s\n", original) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("Modified: %s\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("Replacements made: %zu\n", replaced) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}