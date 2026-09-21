#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void remove_multiple_spaces(char *str)
{
    size_t read_idx = 0;
    size_t write_idx = 0;
    int prev_space = 0;

    if (str == NULL) {
        return;
    }

    while (str[read_idx] != '\0') {
        if (str[read_idx] == ' ') {
            if (!prev_space) {
                str[write_idx] = str[read_idx];
                write_idx++;
            }
            prev_space = 1;
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
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    remove_multiple_spaces(buffer);

    if (printf("Result: %s\n", buffer) < 0) {
        fprintf(stderr, "Error writing output\n");
        return 1;
    }

    return 0;
}