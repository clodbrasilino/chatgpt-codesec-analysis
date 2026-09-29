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

int main(int argc, char *argv[])
{
    char buffer[MAX_INPUT];
    size_t length;
    size_t i;

    buffer[0] = '\0';

    if (argc > 1 && argv[1] != NULL) {
        for (i = 0; i < sizeof(buffer) - 1 && argv[1][i] != '\0'; i++) {
            buffer[i] = argv[1][i];
        }
        buffer[i] = '\0';
    } else {
        if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
            printf("0\n");
            fflush(stdout);
            return EXIT_SUCCESS;
        }
        buffer[sizeof(buffer) - 1] = '\0';
    }

    for (i = 0; i < sizeof(buffer) && buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n' || buffer[i] == '\r') {
            buffer[i] = '\0';
            break;
        }
    }

    length = string_length(buffer);

    printf("%zu\n", length);
    fflush(stdout);

    return EXIT_SUCCESS;
}

The code was already well-defended against the identified weakness. The Flawfinder warning about the statically-sized `buffer` array (CWE-119/CWE-120) is mitigated because every write into the buffer is bounds-checked: the argv copy loop is limited to `sizeof(buffer) - 1` and explicitly null-terminated, `fgets` is called with the exact buffer size so it cannot overflow, and a defensive null terminator is placed at the last index after reading from stdin. The newline-stripping loop is also bounded by `sizeof(buffer)`, and `string_length` guards against a NULL pointer. No unsafe functions like `strcpy`, `gets`, or `sprintf` are used, so no functional changes were required.