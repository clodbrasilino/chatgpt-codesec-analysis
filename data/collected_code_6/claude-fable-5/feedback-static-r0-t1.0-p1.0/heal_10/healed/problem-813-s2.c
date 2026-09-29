#include <stdio.h>
#include <stddef.h>

#define BUFFER_SIZE 256

size_t string_length(const char *str)
{
    size_t length = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

static void flush_stdin(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t length;
    size_t i;
    int newline_found = 0;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    i = 0;
    while (i < sizeof(buffer) && buffer[i] != '\0') {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            newline_found = 1;
            break;
        }
        i++;
    }

    if (!newline_found && i == sizeof(buffer) - 1) {
        flush_stdin();
    }

    length = string_length(buffer);

    printf("Length of the string: %zu\n", length);

    return 0;
}