#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 4096

void capitalize_first_last(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return;
    }

    len = strnlen(str, max_len);
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

    buf_size = sizeof(input);

    if (buf_size == 0 || buf_size > MAX_STR_LEN) {
        fprintf(stderr, "Invalid input size\n");
        return EXIT_FAILURE;
    }

    buffer = malloc(buf_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (strnlen(input, sizeof(input)) >= buf_size) {
        fprintf(stderr, "Source data too large for destination buffer\n");
        free(buffer);
        return EXIT_FAILURE;
    }

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