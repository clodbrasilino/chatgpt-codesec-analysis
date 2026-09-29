#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

bool all_chars_unique(const char *str, size_t max_len)
{
    bool seen[UCHAR_MAX + 1] = { false };
    size_t i;

    if (str == NULL) {
        return false;
    }

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return false;
        }
        seen[c] = true;
    }

    return true;
}

int main(void)
{
    char *buffer;

    buffer = calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    buffer[BUFFER_SIZE - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    if (all_chars_unique(buffer, BUFFER_SIZE)) {
        printf("All characters are unique\n");
    } else {
        printf("Duplicate characters found\n");
    }

    free(buffer);
    return 0;
}