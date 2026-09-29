#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

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
    char buffer[BUFFER_SIZE];

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    if (all_chars_unique(buffer, sizeof(buffer))) {
        printf("All characters are unique\n");
    } else {
        printf("Duplicate characters found\n");
    }

    return 0;
}