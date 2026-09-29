#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void find_sequences(const char *str, size_t max_len)
{
    size_t i = 0;
    size_t len = 0;

    if (str == NULL || max_len == 0) {
        fprintf(stderr, "Error: Invalid input\n");
        return;
    }

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    while (i < len) {
        if (isupper((unsigned char)str[i])) {
            size_t start = i;
            size_t end = i + 1;

            while (end < len && islower((unsigned char)str[end])) {
                end++;
            }

            if (end > start + 1) {
                printf("Sequence found: ");
                for (size_t j = start; j < end; j++) {
                    putchar(str[j]);
                }
                putchar('\n');
            }

            i = end;
        } else {
            i++;
        }
    }
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;

    printf("Enter a string: ");

    read_len = getline(&buffer, &buffer_size, stdin);

    if (read_len == -1) {
        fprintf(stderr, "Error: Failed to read input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (read_len > 0 && buffer[read_len - 1] == '\n') {
        buffer[read_len - 1] = '\0';
        read_len--;
    }

    find_sequences(buffer, (size_t)read_len + 1);

    free(buffer);

    return EXIT_SUCCESS;
}