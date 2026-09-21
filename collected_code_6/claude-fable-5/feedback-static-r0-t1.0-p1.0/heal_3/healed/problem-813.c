#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 256

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

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

int main(void)
{
    char buffer[MAX_INPUT];
    size_t length;

    printf("Enter a string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    length = string_length(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        length--;
        printf("You entered: %s\n", buffer);
    } else if (length == sizeof(buffer) - 1) {
        flush_stdin();
        printf("You entered (truncated): %s\n", buffer);
    } else {
        printf("You entered: %s\n", buffer);
    }

    printf("Length of the string: %zu\n", length);

    return EXIT_SUCCESS;
}