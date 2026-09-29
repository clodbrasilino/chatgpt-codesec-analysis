#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 1024

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t n = 0;

    while (n < max_len && str[n] != '\0') {
        n++;
    }

    return n;
}

void capitalize_first_last(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return;
    }

    len = bounded_strlen(str, max_len);
    i = 0;

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }

        if (i >= len) {
            break;
        }

        {
            size_t start = i;
            size_t end;

            while (i < len && !isspace((unsigned char)str[i])) {
                i++;
            }

            end = i - 1;

            str[start] = (char)toupper((unsigned char)str[start]);
            str[end] = (char)toupper((unsigned char)str[end]);
        }
    }
}

int main(void)
{
    static const char input[] = "hello world this is a test";
    size_t buf_size;
    char *buffer;

    /* Possible weaknesses found:
     *  Assignment 'buf_size=sizeof(input)', assigned value is 27
     */
    buf_size = sizeof(input);

    /* Possible weaknesses found:
     *  Condition 'buf_size==0' is always false
     *  Condition 'buf_size==0' is always false [knownConditionTrueFalse]
     */
    if (buf_size == 0 || buf_size > MAX_STR_LEN) {
        fprintf(stderr, "Invalid input size\n");
        return EXIT_FAILURE;
    }

    buffer = malloc(buf_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, input, buf_size);
    buffer[buf_size - 1] = '\0';

    capitalize_first_last(buffer, buf_size);

    if (printf("Original: %s\n", input) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("Modified: %s\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);

    return EXIT_SUCCESS;
}