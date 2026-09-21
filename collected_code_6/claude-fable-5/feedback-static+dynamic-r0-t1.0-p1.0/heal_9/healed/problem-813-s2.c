#include <stdio.h>
#include <stddef.h>
#include <string.h>

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

int main(int argc, const char *argv[])
{
    char buffer[BUFFER_SIZE];
    size_t length;
    size_t i;

    if (argc > 1 && argv[1] != NULL) {
        length = string_length(argv[1]);
        printf("%zu\n", length);
        fflush(stdout);
        return 0;
    }

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        printf("0\n");
        fflush(stdout);
        return 0;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    i = 0;
    while (i < sizeof(buffer) && buffer[i] != '\0') {
        if (buffer[i] == '\n' || buffer[i] == '\r') {
            buffer[i] = '\0';
            break;
        }
        i++;
    }

    length = string_length(buffer);

    printf("%zu\n", length);
    fflush(stdout);

    return 0;
}