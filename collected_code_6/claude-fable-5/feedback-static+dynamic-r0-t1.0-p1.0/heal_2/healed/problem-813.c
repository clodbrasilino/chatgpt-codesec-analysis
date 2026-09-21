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

int main(void)
{
    char buffer[MAX_INPUT];
    size_t length;
    size_t i;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    for (i = 0; i < sizeof(buffer) && buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
    }

    length = string_length(buffer);

    printf("%zu\n", length);

    return EXIT_SUCCESS;
}