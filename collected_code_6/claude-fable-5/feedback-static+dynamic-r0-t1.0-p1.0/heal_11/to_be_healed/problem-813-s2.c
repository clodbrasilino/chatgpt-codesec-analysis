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

static void strip_newline(char *buffer, size_t size)
{
    size_t i = 0;

    if (buffer == NULL) {
        return;
    }

    while (i < size && buffer[i] != '\0') {
        if (buffer[i] == '\n' || buffer[i] == '\r') {
            buffer[i] = '\0';
            break;
        }
        i++;
    }
}

int main(int argc, const char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t length;

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

    strip_newline(buffer, sizeof(buffer));

    length = string_length(buffer);

    printf("%zu\n", length);
    fflush(stdout);

    return 0;
}