#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void remove_non_alnum(char *str)
{
    size_t read_idx;
    size_t write_idx;

    if (str == NULL) {
        return;
    }

    read_idx = 0;
    write_idx = 0;

    while (str[read_idx] != '\0') {
        if (isalnum((unsigned char)str[read_idx])) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }

    str[write_idx] = '\0';
}

int main(void)
{
    char buffer[256];
    const char *input = "Hello, World! 123 #$% foo_bar";
    int written;

    written = snprintf(buffer, sizeof(buffer), "%s", input);
    if (written < 0 || (size_t)written >= sizeof(buffer)) {
        fprintf(stderr, "Input too long or encoding error\n");
        return EXIT_FAILURE;
    }

    printf("Before: %s\n", buffer);

    remove_non_alnum(buffer);

    printf("After:  %s\n", buffer);

    return EXIT_SUCCESS;
}