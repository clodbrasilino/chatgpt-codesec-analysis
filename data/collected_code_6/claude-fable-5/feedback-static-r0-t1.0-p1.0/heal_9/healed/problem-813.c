#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 256
#define FLUSH_GUARD_MAX 1000000

static size_t string_length(const char *str, size_t max_len)
{
    size_t length = 0;

    if (str == NULL) {
        return 0;
    }

    while (length < max_len && str[length] != '\0') {
        length++;
    }

    return length;
}

static void flush_stdin(void)
{
    int ch;
    size_t guard = 0;

    do {
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < FLUSH_GUARD_MAX);
}

int main(void)
{
    char buffer[MAX_INPUT] = {0};
    size_t length;

    printf("Enter a string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    length = string_length(buffer, sizeof(buffer));

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