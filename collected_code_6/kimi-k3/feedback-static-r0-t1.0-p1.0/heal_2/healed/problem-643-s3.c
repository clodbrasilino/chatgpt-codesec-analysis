#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool match_z_not_ends(const char *word, size_t max_len)
{
    size_t len;
    size_t i;

    if (word == NULL) {
        return false;
    }

    len = strnlen(word, max_len);
    if (len < 3U) {
        return false;
    }

    for (i = 1U; i < len - 1U; i++) {
        if (word[i] == 'z') {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char buffer[256];
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        len = strcspn(buffer, "\n");
        buffer[len] = '\0';
        if (match_z_not_ends(buffer, sizeof(buffer))) {
            printf("Match\n");
        } else {
            printf("No match\n");
        }
    }

    return 0;
}