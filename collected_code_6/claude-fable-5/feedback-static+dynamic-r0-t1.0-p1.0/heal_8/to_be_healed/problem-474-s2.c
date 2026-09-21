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
    size_t buffer_size;
    size_t source_len;
    char *buffer;
    size_t replaced;

    /* Possible weaknesses found:
     *  Assignment 'source_len=sizeof(original)', assigned value is 28
     */
    source_len = sizeof(original);
    /* Possible weaknesses found:
     *  Assignment 'buffer_size=source_len', assigned value is 28
     *  buffer_size is assigned 'source_len' here.
     */
    buffer_size = source_len;

    buffer = malloc(buffer_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Condition 'source_len>buffer_size' is always false [knownConditionTrueFalse]
     *  Condition 'source_len>buffer_size' is always false
     */
    if (source_len > buffer_size) {
        fprintf(stderr, "Source data exceeds destination buffer\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, original, source_len);
    buffer[buffer_size - 1] = '\0';

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