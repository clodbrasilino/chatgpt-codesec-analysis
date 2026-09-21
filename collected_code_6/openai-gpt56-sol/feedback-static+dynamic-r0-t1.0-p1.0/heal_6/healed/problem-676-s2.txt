#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_non_alphanumeric(char *string, size_t capacity)
{
    size_t read_pos = 0;
    size_t write_pos = 0;

    if (string == NULL || capacity == 0) {
        return -1;
    }

    while (read_pos < capacity) {
        unsigned char c = (unsigned char)string[read_pos++];

        if (c == '\0') {
            string[write_pos] = '\0';
            return 0;
        }

        if ((c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
            (c >= (unsigned char)'A' && c <= (unsigned char)'Z') ||
            (c >= (unsigned char)'a' && c <= (unsigned char)'z')) {
            string[write_pos++] = (char)c;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *string;
    size_t length;
    size_t capacity;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            (argc > 0 && argv != NULL && argv[0] != NULL)
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    input = argv[1];
    length = strnlen(input, SIZE_MAX);

    if (length == SIZE_MAX) {
        fprintf(stderr, "Input is too large or not null-terminated\n");
        return EXIT_FAILURE;
    }

    capacity = length + 1;
    string = malloc(capacity);

    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(string, input, capacity);

    if (remove_non_alphanumeric(string, capacity) != 0) {
        fprintf(stderr, "Failed to process string\n");
        free(string);
        return EXIT_FAILURE;
    }

    puts(string);
    free(string);

    return EXIT_SUCCESS;
}