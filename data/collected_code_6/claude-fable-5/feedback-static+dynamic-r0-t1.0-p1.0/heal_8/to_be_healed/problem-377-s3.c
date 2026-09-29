#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_char(char *str, char c)
{
    size_t read_idx = 0;
    size_t write_idx = 0;

    if (str == NULL) {
        return;
    }

    while (str[read_idx] != '\0') {
        if (str[read_idx] != c) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    str[write_idx] = '\0';
}

int main(void)
{
    const char source[] = "hello world, hello everyone";
    char target = 'l';
    size_t source_len;
    size_t buffer_size;
    char *buffer;

    source_len = strnlen(source, sizeof(source));
    if (source_len >= sizeof(source)) {
        fprintf(stderr, "Source string is not null-terminated\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  buffer_size is assigned 'source_len+1' here.
     */
    buffer_size = source_len + 1;
    buffer = malloc(buffer_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Condition 'source_len>=buffer_size' is always false
     *  Condition 'source_len>=buffer_size' is always false [knownConditionTrueFalse]
     */
    if (source_len >= buffer_size) {
        fprintf(stderr, "Destination buffer too small\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, source, source_len);
    buffer[source_len] = '\0';

    printf("Original string: %s\n", buffer);
    remove_char(buffer, target);
    printf("After removing '%c': %s\n", target, buffer);

    free(buffer);

    return EXIT_SUCCESS;
}