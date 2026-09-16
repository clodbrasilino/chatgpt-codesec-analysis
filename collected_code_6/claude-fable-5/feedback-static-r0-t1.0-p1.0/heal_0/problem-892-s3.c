#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char buffer[256];
    const char *test = "This   is  a    string   with  multiple    spaces";

    if (strlen(test) >= sizeof(buffer)) {
        fprintf(stderr, "Input string too long\n");
        return EXIT_FAILURE;
    }

    strncpy(buffer, test, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    printf("Before: \"%s\"\n", buffer);

    remove_multiple_spaces(buffer);

    printf("After:  \"%s\"\n", buffer);

    return EXIT_SUCCESS;
}