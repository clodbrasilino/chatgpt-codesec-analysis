#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    const char source[] = "hello world, hello everyone";
    char target = 'l';
    size_t source_len;
    char *buffer;

    source_len = strlen(source);

    buffer = malloc(source_len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, source, source_len);
    buffer[source_len] = '\0';

    printf("Original string: %s\n", buffer);
    remove_char(buffer, target);
    printf("After removing '%c': %s\n", target, buffer);

    free(buffer);

    return EXIT_SUCCESS;
}