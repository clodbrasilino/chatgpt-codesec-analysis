#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 256

bool all_chars_unique(const char *str, size_t max_len)
{
    bool seen[256] = { false };
    size_t i;
    size_t len;

    if (str == NULL) {
        return false;
    }

    len = strnlen(str, max_len);

    for (i = 0; i < len; i++) {
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

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
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