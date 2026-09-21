#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void remove_char(char *str, char c)
{
    size_t read_idx = 0;
    size_t write_idx = 0;

    if (str == NULL) {
        return;
    }

    while (str[read_idx] != '\0') {
        if (str[read_idx] != c) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    str[write_idx] = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    const char *source = "hello world, hello everyone";
    char target = 'l';
    size_t source_len;
    int written;

    source_len = strnlen(source, sizeof(buffer));
    if (source_len >= sizeof(buffer)) {
        fprintf(stderr, "Source string too long\n");
        return EXIT_FAILURE;
    }

    written = snprintf(buffer, sizeof(buffer), "%s", source);
    if (written < 0 || (size_t)written >= sizeof(buffer)) {
        fprintf(stderr, "Failed to copy source string\n");
        return EXIT_FAILURE;
    }

    printf("Original string: %s\n", buffer);
    remove_char(buffer, target);
    printf("After removing '%c': %s\n", target, buffer);

    return EXIT_SUCCESS;
}