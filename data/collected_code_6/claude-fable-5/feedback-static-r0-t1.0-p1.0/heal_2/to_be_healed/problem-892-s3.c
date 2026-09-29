#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void remove_multiple_spaces(char *str)
{
    size_t read_idx;
    size_t write_idx;
    int prev_space;

    if (str == NULL) {
        return;
    }

    read_idx = 0;
    write_idx = 0;
    prev_space = 0;

    while (str[read_idx] != '\0') {
        if (str[read_idx] == ' ') {
            if (!prev_space) {
                str[write_idx] = str[read_idx];
                write_idx++;
                prev_space = 1;
            }
        } else {
            str[write_idx] = str[read_idx];
            write_idx++;
            prev_space = 0;
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
    const char *test = "This   is  a    string   with  multiple    spaces";
    size_t test_len;
    int written;

    test_len = strnlen(test, sizeof(buffer));
    if (test_len >= sizeof(buffer)) {
        fprintf(stderr, "Input string too long\n");
        return EXIT_FAILURE;
    }

    written = snprintf(buffer, sizeof(buffer), "%s", test);
    if (written < 0 || (size_t)written >= sizeof(buffer)) {
        fprintf(stderr, "Failed to copy input string\n");
        return EXIT_FAILURE;
    }

    printf("Before: \"%s\"\n", buffer);

    remove_multiple_spaces(buffer);

    printf("After:  \"%s\"\n", buffer);

    return EXIT_SUCCESS;
}