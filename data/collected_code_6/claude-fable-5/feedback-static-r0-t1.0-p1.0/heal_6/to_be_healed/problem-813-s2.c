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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t length;
    size_t i;

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
            break;
        }
        i++;
    }

    length = string_length(buffer);

    printf("Length of the string: %zu\n", length);

    return 0;
}