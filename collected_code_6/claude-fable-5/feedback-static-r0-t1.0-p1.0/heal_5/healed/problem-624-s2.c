#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 255

char *string_to_upper(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return NULL;
    }

    len = strnlen(str, max_len);
    if (len == max_len) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        str[i] = (char)toupper((unsigned char)str[i]);
    }

    return str;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    char *result;

    printf("Enter a string: ");

    bytes_read = getline(&buffer, &buffer_size, stdin);
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if ((size_t)bytes_read > MAX_INPUT_LEN) {
        fprintf(stderr, "Input too long\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = string_to_upper(buffer, buffer_size);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Uppercase: %s\n", result);

    free(buffer);
    return EXIT_SUCCESS;
}