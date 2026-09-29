#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

void remove_whitespace(char *str)
{
    if (str == NULL) {
        return;
    }

    size_t read_index = 0;
    size_t write_index = 0;

    while (str[read_index] != '\0') {
        if (!isspace((unsigned char)str[read_index])) {
            str[write_index] = str[read_index];
            write_index++;
        }
        read_index++;
    }
    str[write_index] = '\0';
}

int main(void)
{
    const char original[] = "  Hello,   World! \t This is a test.\n";

    size_t len = strnlen(original, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input string too long or not null-terminated\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  buffer_size is assigned 'len+1' here.
     */
    size_t buffer_size = len + 1;
    char *buffer = malloc(buffer_size);
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
        fprintf(stderr, "Buffer size insufficient for copy\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, original, len);
    buffer[len] = '\0';

    remove_whitespace(buffer);

    if (printf("Original: \"%s\"\n", original) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }
    if (printf("Result:   \"%s\"\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}