#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_INPUT_LEN 256

bool all_chars_unique(const char *str, size_t max_len)
{
    bool seen[256] = { false };
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
    char buffer[MAX_INPUT_LEN];

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